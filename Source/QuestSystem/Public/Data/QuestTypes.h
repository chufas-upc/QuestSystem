#pragma once

#include "CoreMinimal.h"
#include "QuestTypes.generated.h"

class UQuestDefinition;

UENUM(BlueprintType)
enum class EQuestObjectiveType : uint8
{
	Kill            UMETA(DisplayName = "Kill"),
	Collect         UMETA(DisplayName = "Collect"),
	Interact        UMETA(DisplayName = "Interact"),
	ReachLocation   UMETA(DisplayName = "ReachLocation")
};

USTRUCT(BlueprintType)
struct QUESTSYSTEM_API FQuestObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FName ObjetiveID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	EQuestObjectiveType ObjetiveType = EQuestObjectiveType::Kill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FName TargetID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	int32 RequiredAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	int32 CurrentAmount = 0;
};

USTRUCT(BlueprintType)
struct QUESTSYSTEM_API FQuestRuntime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName QuestID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TObjectPtr<UQuestDefinition> QuestDefinition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestObjective> Objetives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool IsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool IsCompleted = false;
};
