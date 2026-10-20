#include "Actors/CoinCollector.h"
#include "Game/QuestGameState.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

ACoinCollector::ACoinCollector()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(50.f);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void ACoinCollector::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (TextRenderComponent)
	{
		const UEnum* EnumPtr = StaticEnum<EQuestObjectiveType>();
		FString TypeStr = EnumPtr ? EnumPtr->GetNameStringByValue(static_cast<int64>(TargetType)) : TEXT("");
		FText DisplayText = FText::Format(
			FText::FromString(TEXT("{0} {1}")),
			FText::FromString(TypeStr),
			FText::FromName(TargetID)
		);
		TextRenderComponent->SetText(DisplayText);
	}
}

void ACoinCollector::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (UWorld* World = GetWorld())
	{
		if (AQuestGameState* QuestGameState = Cast<AQuestGameState>(UGameplayStatics::GetGameState(World)))
		{
			QuestGameState->ReportGameplayObjective(TargetType, TargetID, Amount);
		}
	}
}
