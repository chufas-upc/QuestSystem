#include "Game/QuestGameState.h"

void AQuestGameState::ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	OnGameplayObjectiveEvent.Broadcast(ObjectiveType, TargetID, Amount);
}
