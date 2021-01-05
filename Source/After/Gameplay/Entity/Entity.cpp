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
	CurrentDirection(FDirection::L),
	bIsRunning(false),
	bIsMoving(true)
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

	if (bIsMoving)
	{
		const float SQRT_2 = 1.41421f;

		float Delta = (bIsRunning ? EntityData.RunSpeed : EntityData.WalkSpeed) * DeltaTime;
		float Sqrt2_Delta = SQRT_2 * Delta;
		FVector Offset;
		switch (CurrentDirection)
		{
		case FDirection::F:
		{
			Offset = FVector(0.f, -Delta, 0.f);
			break;
		}
		case FDirection::FR:
		{
			Offset = FVector(Sqrt2_Delta, -Sqrt2_Delta, 0.f);
			break;
		}
		case FDirection::R:
		{
			Offset = FVector(Delta, 0.f, 0.f);
			break;
		}
		case FDirection::BR:
		{
			Offset = FVector(Sqrt2_Delta, Sqrt2_Delta, 0.f);
			break;
		}
		case FDirection::B:
		{
			Offset = FVector(0.f, Delta, 0.f);
			break;
		}
		case FDirection::BL:
		{
			Offset = FVector(-Sqrt2_Delta, Sqrt2_Delta, 0.f);
			break;
		}
		case FDirection::L:
		{
			Offset = FVector(-Delta, 0.f, 0.f);
			break;
		}
		case FDirection::FL:
		{
			Offset = FVector(-Sqrt2_Delta, -Sqrt2_Delta, 0.f);
			break;
		}
		}
		AddActorLocalOffset(Offset, true);
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

		FlipbookComponent->SetFlipbook(EntityData.Flipbooks[FEntityStatus::STAY].Flipbooks[CurrentDirection]);
	}
}

void AEntity::SetIsMoving(const bool IsMoving)
{
	bIsMoving = IsMoving;
	SetFlipbook();
}

void AEntity::SetIsRunning(const bool IsRunning)
{
	bIsRunning = IsRunning;
	SetFlipbook();
}

void AEntity::SetDirection(const FDirection Direction)
{
	CurrentDirection = Direction;
	SetFlipbook();
}

void AEntity::SetFlipbook()
{
	FEntityStatus Status = bIsMoving ? (bIsRunning ? FEntityStatus::RUN : FEntityStatus::WALK) : FEntityStatus::STAY;
	FlipbookComponent->SetFlipbook(EntityData.Flipbooks[Status].Flipbooks[CurrentDirection]);
}