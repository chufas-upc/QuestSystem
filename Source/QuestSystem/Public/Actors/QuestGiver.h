#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "QuestGiver.generated.h"

class UQuestDefinition;
class USceneComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS(BlueprintType)
class QUESTSYSTEM_API AQuestGiver : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AQuestGiver();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TObjectPtr<UQuestDefinition> QuestDefinition;

	virtual void Interact_Implementation(AActor* Interactor) override;
};
