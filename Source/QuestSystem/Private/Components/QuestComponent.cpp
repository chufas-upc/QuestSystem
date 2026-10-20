#include "Components/QuestComponent.h"
#include "Game/QuestGameState.h"
#include "Data/QuestDefinition.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (AQuestGameState* QuestGameState = Cast<AQuestGameState>(UGameplayStatics::GetGameState(World)))
		{
			QuestGameState->OnGameplayObjectiveEvent.AddDynamic(this, &UQuestComponent::HandleGameplayObjective);
		}
	}
}

void UQuestComponent::AddQuest(UQuestDefinition* QuestDefinition)
{
	if (!QuestDefinition)
	{
		return;
	}

	bool bFound = false;
	FQuestRuntime ExistingQuest;
	int32 FoundIndex = -1;
	FindQuestByID(QuestDefinition->QuestID, bFound, ExistingQuest, FoundIndex);

	if (bFound)
	{
		return;
	}

	FQuestRuntime NewQuest;
	NewQuest.QuestID = QuestDefinition->QuestID;
	NewQuest.QuestDefinition = QuestDefinition;
	NewQuest.Objetives = QuestDefinition->Objetives;
	NewQuest.IsActive = true;
	NewQuest.IsCompleted = false;

	ActiveQuest.Add(NewQuest);
	OnQuestStarted.Broadcast(NewQuest);
}

void UQuestComponent::FindQuestByID(FName QuestID, bool& Found, FQuestRuntime& QuestData, int32& QuestIndex)
{
	for (int32 i = 0; i < ActiveQuest.Num(); ++i)
	{
		if (ActiveQuest[i].QuestID == QuestID)
		{
			Found = true;
			QuestData = ActiveQuest[i];
			QuestIndex = i;
			return;
		}
	}

	Found = false;
	QuestData = FQuestRuntime();
	QuestIndex = -1;
}

void UQuestComponent::HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	for (int32 QuestIdx = 0; QuestIdx < ActiveQuest.Num(); ++QuestIdx)
	{
		FQuestRuntime& Quest = ActiveQuest[QuestIdx];
		if (Quest.IsActive && !Quest.IsCompleted)
		{
			for (int32 ObjIdx = 0; ObjIdx < Quest.Objetives.Num(); ++ObjIdx)
			{
				const FQuestObjective& Objective = Quest.Objetives[ObjIdx];
				if (Objective.ObjetiveType == ObjectiveType && Objective.TargetID == TargetID)
				{
					UpdateObjectiveProgress(QuestIdx, ObjIdx, Amount);
				}
			}
		}
	}
}

void UQuestComponent::UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount)
{
	if (!ActiveQuest.IsValidIndex(QuestIndex))
	{
		return;
	}

	if (!ActiveQuest[QuestIndex].Objetives.IsValidIndex(ObjectiveIndex))
	{
		return;
	}

	FQuestObjective& Objective = ActiveQuest[QuestIndex].Objetives[ObjectiveIndex];
	Objective.CurrentAmount = FMath::Min(Objective.CurrentAmount + Amount, Objective.RequiredAmount);

	CheckQuestCompleted(QuestIndex);
	OnQuestProgressChanged.Broadcast(ActiveQuest[QuestIndex]);
}

void UQuestComponent::CheckQuestCompleted(int32 QuestIndex)
{
	if (!ActiveQuest.IsValidIndex(QuestIndex))
	{
		return;
	}

	bool bHasIncompleteObjectives = false;
	for (const FQuestObjective& Obj : ActiveQuest[QuestIndex].Objetives)
	{
		if (Obj.CurrentAmount < Obj.RequiredAmount)
		{
			bHasIncompleteObjectives = true;
			break;
		}
	}

	if (!bHasIncompleteObjectives)
	{
		ActiveQuest[QuestIndex].IsCompleted = true;
		OnQuestCompleted.Broadcast(ActiveQuest[QuestIndex]);
	}
}
