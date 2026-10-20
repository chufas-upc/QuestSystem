#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/QuestTypes.h"
#include "QuestDefinition.generated.h"

UCLASS(BlueprintType)
class QUESTSYSTEM_API UQuestDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName QuestID = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestObjective> Objetives;
};
