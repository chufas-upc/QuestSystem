#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuestController.generated.h"

class UQuestComponent;
class UUserWidget;

UCLASS(BlueprintType)
class QUESTSYSTEM_API AQuestController : public APlayerController
{
	GENERATED_BODY()

public:
	AQuestController();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UQuestComponent> QuestComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> TrackerWidgetClass;
};
