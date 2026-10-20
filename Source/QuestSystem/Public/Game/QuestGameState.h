#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/QuestTypes.h"
#include "QuestGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGameplayObjectiveEvent, EQuestObjectiveType, ObjectiveType, FName, TargetID, int32, Amount);

UCLASS(BlueprintType)
class QUESTSYSTEM_API AQuestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnGameplayObjectiveEvent OnGameplayObjectiveEvent;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);
};
