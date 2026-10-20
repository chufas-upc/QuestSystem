#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/QuestTypes.h"
#include "QuestComponent.generated.h"

class UQuestDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStarted, const FQuestRuntime&, QuestData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestProgressChanged, const FQuestRuntime&, QuestData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, const FQuestRuntime&, QuestData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestComponent();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestStarted OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestProgressChanged OnQuestProgressChanged;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestCompleted OnQuestCompleted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestRuntime> ActiveQuest;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuest(UQuestDefinition* QuestDefinition);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void FindQuestByID(FName QuestID, bool& Found, FQuestRuntime& QuestData, int32& QuestIndex);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CheckQuestCompleted(int32 QuestIndex);
};
