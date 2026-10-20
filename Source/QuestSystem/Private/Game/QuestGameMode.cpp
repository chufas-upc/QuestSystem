#include "Game/QuestGameMode.h"
#include "Game/QuestGameState.h"
#include "Game/QuestController.h"

AQuestGameMode::AQuestGameMode()
{
	GameStateClass = AQuestGameState::StaticClass();
	PlayerControllerClass = AQuestController::StaticClass();
}
