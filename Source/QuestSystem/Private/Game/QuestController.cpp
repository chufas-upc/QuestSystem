#include "Game/QuestController.h"
#include "Components/QuestComponent.h"
#include "Blueprint/UserWidget.h"

AQuestController::AQuestController()
{
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
}

void AQuestController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && TrackerWidgetClass)
	{
		if (UUserWidget* TrackerWidget = CreateWidget<UUserWidget>(this, TrackerWidgetClass))
		{
			TrackerWidget->AddToViewport();
		}
	}
}
