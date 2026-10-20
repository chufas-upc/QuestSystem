#include "Actors/QuestGiver.h"
#include "Components/QuestComponent.h"
#include "Data/QuestDefinition.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

AQuestGiver::AQuestGiver()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AQuestGiver::Interact_Implementation(AActor* Interactor)
{
	if (Interactor && QuestDefinition)
	{
		if (UQuestComponent* QuestComp = Interactor->FindComponentByClass<UQuestComponent>())
		{
			QuestComp->AddQuest(QuestDefinition);
		}
	}
}
