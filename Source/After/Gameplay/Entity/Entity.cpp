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
	bIsRunning(false)
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 8.f));

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(GetRootComponent());
	FlipbookComponent->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

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
		CollisionComponent->SetBoxExtent(FVector(EntityData.SizeX, EntityData.SizeY, 8.f));

// Checking if there are textures
		bool HasTexture = false;
		for (FEntityStatus i = FEntityStatus::BEGIN; i <= FEntityStatus::END; ++i)
		{
			if (!EntityData.Flipbooks.Contains(i))
			{
				EntityData.Flipbooks.Add(i, FEntityFlipbooks());
			}

			for (FDirection j = FDirection::BEGIN; j <= FDirection::END; ++j)
			{
				if (!EntityData.Flipbooks[i].Flipbooks.Contains(j))
				{
					EntityData.Flipbooks[i].Flipbooks.Add(j, EntityDatabase->GetEntityDebugFlipbooks()[j]);
					HasTexture = false;
				}
			}
		}

		if (!HasTexture)
		{
			UE_LOG(LogTemp, Error, TEXT("There is no flipbooks for the entity %s"), *Id.ToString());
		}
		FlipbookComponent->SetFlipbook(EntityData.Flipbooks[FEntityStatus::STAY].Flipbooks[CurrentDirection]);
	}
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntity::Move(const FDirection Direction)
{
	
}