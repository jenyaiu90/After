    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Entity.cpp                  //
////////////////////////////////////////

#include "Entity.h"

#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

#include "../../AfterGameModeBase.h"

AEntity::AEntity() :
	CurrentDirection(FDirection::F),
	CurrentStatus(FEntityStatus::STAY),
	bIsRunning(false),
	MovementX(0),
	MovementY(0)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 8.f));

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(GetRootComponent());
	FlipbookComponent->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float SQRT_2 = 1.41421f;

	FVector Offset(MovementX, MovementY, 0.f);
	if (!Offset.IsZero())
	{
		Offset *= (bIsRunning ? EntityData.RunSpeed : EntityData.WalkSpeed) * DeltaTime;
		if (MovementX != 0 && MovementY != 0)
		{
			Offset /= SQRT_2;
		}
		AddActorLocalOffset(Offset, true);

		FDirection RequiredDirection;
		if (MovementY < 0)
		{
			RequiredDirection = FDirection::F;
		}
		else if (MovementY > 0)
		{
			RequiredDirection = FDirection::B;
		}
		else if (MovementX < 0)
		{
			RequiredDirection = FDirection::L;
		}
		else
		{
			RequiredDirection = FDirection::R;
		}
		if (CurrentDirection != RequiredDirection)
		{
			FlipbookComponent->SetFlipbook(EntityData.Flipbooks[CurrentStatus].Flipbooks[RequiredDirection]);
			CurrentDirection = RequiredDirection;
		}

		FEntityStatus RequiredStatus = bIsRunning ? FEntityStatus::RUN : FEntityStatus::WALK;
		if (CurrentStatus != RequiredStatus)
		{
			FlipbookComponent->SetFlipbook(EntityData.Flipbooks[RequiredStatus].Flipbooks[CurrentDirection]);
			CurrentStatus = RequiredStatus;
		}
	}
	else
	{
		if (CurrentStatus != FEntityStatus::STAY)
		{
			FlipbookComponent->SetFlipbook(EntityData.Flipbooks[FEntityStatus::STAY].Flipbooks[CurrentDirection]);
			CurrentStatus = FEntityStatus::STAY;
		}
	}
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	AAfterGameModeBase* AfterGameMode;
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load a data of an entity %s because its tag is not valid"), *Id.ToString());
	}
	else if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load a data of an entity %s because the world wasn't found"), *Id.ToString());
	}
	else if (AfterGameMode = Cast<AAfterGameModeBase>(GetWorld()->GetAuthGameMode()),
		!AfterGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load a data of an entity %s because the gamemode wasn't found"), *Id.ToString());
	}
	else
	{
		UDA_Database* EntityDatabase = AfterGameMode->GetDatabase();
		EntityData = EntityDatabase->GetEntityData(Id);

		Health = EntityData.MaxHealth;
		CollisionComponent->SetBoxExtent(FVector(EntityData.SizeX * 32.f, EntityData.SizeY * 32.f, 8.f));

		// If the game chashes here, most likely you should just add a data about your entity in the database
		FlipbookComponent->SetFlipbook(EntityData.Flipbooks[FEntityStatus::STAY].Flipbooks[CurrentDirection]);
	}
}
