#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/QuestTypes.h"
#include "CoinCollector.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS(BlueprintType)
class QUESTSYSTEM_API ACoinCollector : public AActor
{
	GENERATED_BODY()

public:
	ACoinCollector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FName TargetID = FName(TEXT("collect"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	EQuestObjectiveType TargetType = EQuestObjectiveType::Collect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	int32 Amount = 1;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
