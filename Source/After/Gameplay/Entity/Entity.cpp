    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Entity.cpp                  //
////////////////////////////////////////

#include "Entity.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

#include "../../AfterGameModeBase.h"
#include "Last/LastController.h"

AEntity::AEntity() :
	CurrentDirection(FDirection::F),
	CurrentStatus(FEntityStatus::Stay),
	bIsDead(false),
	bIsRunning(false),
	MovementX(0),
	MovementY(0),
	bIsTextureBlocked(false)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 8.f));
	CollisionComponent->SetCollisionProfileName(FName("Entity"));

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(GetRootComponent());
	FlipbookComponent->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDead)
	{
		const float Sqrt_2 = 1.41421f;

		FVector Offset(MovementX, MovementY, 0.f);
		if (!Offset.IsZero())
		{
			if (bIsRunning && Energy <= 0.f)
			{
				Energy = 0.f;
				StopRunning();
			}
			Offset *= (bIsRunning ? EntityData->RunSpeed : EntityData->WalkSpeed) * DeltaTime;
			if (MovementX != 0 && MovementY != 0)
			{
				Offset /= Sqrt_2;
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
				FlipbookComponent->SetFlipbook(EntityData->Flipbooks[CurrentStatus].Flipbooks[RequiredDirection]);
				CurrentDirection = RequiredDirection;
			}

			FEntityStatus RequiredStatus = bIsRunning ? FEntityStatus::Run : FEntityStatus::Walk;
			if (!bIsTextureBlocked && CurrentStatus != RequiredStatus)
			{
				FlipbookComponent->SetFlipbook(EntityData->Flipbooks[RequiredStatus].Flipbooks[CurrentDirection]);
				FlipbookComponent->SetLooping(true);
				CurrentStatus = RequiredStatus;
			}
			if (bIsRunning)
			{
				Energy -= EntityData->EnergySpeed * DeltaTime;
			}
		}
		else
		{
			if (!bIsTextureBlocked && CurrentStatus != FEntityStatus::Stay)
			{
				FlipbookComponent->SetFlipbook(EntityData->Flipbooks[FEntityStatus::Stay].Flipbooks[CurrentDirection]);
				FlipbookComponent->SetLooping(true);
				CurrentStatus = FEntityStatus::Stay;
			}
		}
	}
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntity::StartRunning()
{
	if (Energy > 0.f)
	{
		bIsRunning = true;
	}
}

void AEntity::StopRunning()
{
	bIsRunning = false;
}

void AEntity::MoveX(float Val)
{
	MovementX = FMath::Clamp(Val, -1.f, 1.f);
}

void AEntity::MoveY(float Val)
{
	MovementY = FMath::Clamp(Val, -1.f, 1.f);
}

void AEntity::Damage(float Value, FDamageType DamageType, AEntity* FromWho)
{
	Damage(Value, DamageType);
	if (Health <= 0.f)
	{
		Death(FromWho);
	}
}

void AEntity::Death(AEntity* Murderer)
{
	Death();
}

void AEntity::Select()
{

}

void AEntity::Unselect()
{

}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(StatsTimer, this, &AEntity::CalculateStats, 1.f, true, 1.f);

	FlipbookComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	AAfterGameModeBase* AfterGameMode;
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of an entity %s because its tag is not valid"), *Id.ToString());
	}
	else if (!GetWorld())
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of an entity %s because the world wasn't found"), *Id.ToString());
	}
	else if (AfterGameMode = Cast<AAfterGameModeBase>(GetWorld()->GetAuthGameMode()),
		!AfterGameMode)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Couldn't load a data of an entity %s because the gamemode wasn't found"), *Id.ToString());
	}
	else
	{
		ALastController* LastController = Cast<ALastController>(GetWorld()->GetFirstPlayerController());
		if (LastController)
		{
			OnBeginCursorOver.AddDynamic(LastController, &ALastController::Select);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player controller (ALastController) wasn't found"));
		}

		UDA_Database* Database = AfterGameMode->GetDatabase();
		EntityData = &Database->GetEntityData(Id);

		Health = EntityData->MaxHealth;
		Energy = EntityData->MaxEnergy;
		CollisionComponent->SetBoxExtent(FVector(EntityData->SizeX * 32.f, EntityData->SizeY * 32.f, 8.f));

		// If the game chashes here, most likely you should just add a data about your entity in the database
		FlipbookComponent->SetFlipbook(EntityData->Flipbooks[CurrentStatus].Flipbooks[CurrentDirection]);
	}
}

const FEntityInfo& AEntity::GetEntityData() const
{
	return *EntityData;
}

void AEntity::CalculateStats()
{
	if (!bIsRunning || MovementX == 0.f && MovementY == 0.f)
	{
		Energy = FMath::Clamp(Energy + EntityData->EnergyRegenerationSpeed, 0.f, EntityData->MaxEnergy);
	}
}

bool AEntity::MeleeAttack(AEntity* Attacked)
{
	CurrentStatus = FEntityStatus::MeleeAttack;
	FlipbookComponent->SetFlipbook(EntityData->Flipbooks[CurrentStatus].Flipbooks[CurrentDirection]);
	FlipbookComponent->SetLooping(false);
	GetWorld()->GetTimerManager().SetTimer(TextureTimer, this, &AEntity::UnblockTexture, FlipbookComponent->GetFlipbookLength(), false);
	if (FVector::Dist(Attacked->GetActorLocation(), GetActorLocation()) <= EntityData->MeleeRadius)
	{
		Attacked->Damage(EntityData->MeleeDamage, EntityData->MeleeDamageType, this);
		return true;
	}
	else
	{
		return false;
	}
}

void AEntity::Damage(float Value, FDamageType DamageType)
{
	Health -= Value * EntityData->DamageResist[DamageType];
	CurrentStatus = FEntityStatus::Damage;
	FlipbookComponent->SetFlipbook(EntityData->Flipbooks[CurrentStatus].Flipbooks[CurrentDirection]);
	FlipbookComponent->SetLooping(false);
	GetWorld()->GetTimerManager().SetTimer(TextureTimer, this, &AEntity::UnblockTexture, FlipbookComponent->GetFlipbookLength(), false);
}

void AEntity::Death()
{
	Health = 0.f;
	CurrentStatus = FEntityStatus::Death;
	FlipbookComponent->SetFlipbook(EntityData->Flipbooks[CurrentStatus].Flipbooks[CurrentDirection]);
	FlipbookComponent->SetLooping(false);
	GetWorld()->GetTimerManager().SetTimer(TextureTimer, this, &AEntity::UnblockTexture, 4 * FlipbookComponent->GetFlipbookLength(), false);

	bIsDead = true;
}

void AEntity::UnblockTexture()
{
	bIsTextureBlocked = false;

	if (bIsDead)
	{
		Destroy();
	}
}