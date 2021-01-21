    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Unit.cpp                    //
////////////////////////////////////////

#include "Unit.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

#include "../../AfterGameModeBase.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 8.f));
	CollisionComponent->SetCollisionProfileName(FName("Unit"));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Flipbook"));
	SpriteComponent->SetupAttachment(GetRootComponent());
	SpriteComponent->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();

	SpriteComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	AAfterGameModeBase* AfterGameMode;
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of a unit %s because its tag is not valid"), *Id.ToString());
	}
	else if (!GetWorld())
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of a unit %s because the world wasn't found"), *Id.ToString());
	}
	else if (AfterGameMode = Cast<AAfterGameModeBase>(GetWorld()->GetAuthGameMode()),
		!AfterGameMode)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of a unit %s because the gamemode wasn't found"), *Id.ToString());
	}
	else
	{
		UDA_Database* Database = AfterGameMode->GetDatabase();
		UnitData = Database->GetUnitData(Id);

		CollisionComponent->SetBoxExtent(FVector(UnitData.SizeX * 32.f, UnitData.SizeY * 32.f, 8.f));

		SpriteComponent->SetSprite(UnitData.Sprite);
	}
}

void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
