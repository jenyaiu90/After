    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Unit.cpp                    //
////////////////////////////////////////

#include "Unit.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

#include "../Entity/Entity.h"
#include "../../AfterGameModeBase.h"
#include "../Entity/Last/LastController.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 8.f));
	CollisionComponent->SetCollisionProfileName(FName("Unit"));

	DamageBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	DamageBoxComponent->SetupAttachment(GetRootComponent());
	DamageBoxComponent->SetBoxExtent(FVector(34.f, 34.f, 24.f));
	DamageBoxComponent->SetCollisionProfileName(FName("UnitDamage"));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Flipbook"));
	SpriteComponent->SetupAttachment(GetRootComponent());
	SpriteComponent->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}

void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::Select()
{

}

void AUnit::Unselect()
{

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
		UnitData = &Database->GetUnitData(Id);

		CollisionComponent->SetBoxExtent(FVector(UnitData->SizeX * 32.f, UnitData->SizeY * 32.f, 8.f));
		
		if (UnitData->Damage != 0.f)
		{
			DamageBoxComponent->SetBoxExtent(FVector(UnitData->SizeX * 32.f + 2.f, UnitData->SizeY * 32.f + 2.f, 24.f));
			DamageBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AUnit::BeginOverlap);
			DamageBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AUnit::EndOverlap);
		}
		else
		{
			DamageBoxComponent->DestroyComponent();
		}

		SpriteComponent->SetSprite(UnitData->Sprite);
	}
}

const FUnitInfo& AUnit::GetUnitData() const
{
	return *UnitData;
}

void AUnit::BeginOverlap(UPrimitiveComponent* Component1, AActor* Actor,
	UPrimitiveComponent* Component2, int32 Int, bool Bool, const FHitResult& HitResult)
{
	AEntity* Entity = Cast<AEntity>(Actor);
	if (Entity && !DamageTimers.Contains(Entity))
	{
		DamageTimers.Add(Entity, FTimerHandle());
		GetWorld()->GetTimerManager().SetTimer(DamageTimers[Entity], this, &AUnit::DamageForEntities, 1.f, true, 0.f);
	}
}

void AUnit::EndOverlap(UPrimitiveComponent* Component1, AActor* Actor, UPrimitiveComponent* Component2, int32 Int)
{
	AEntity* Entity = Cast<AEntity>(Actor);
	if (Entity && DamageTimers.Contains(Entity))
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimers[Entity]);
		DamageTimers.Remove(Entity);
	}
}

void AUnit::DamageForEntities()
{
	TArray<AEntity*> Entities;
	DamageTimers.GetKeys(Entities);
	for (AEntity* i : Entities)
	{
		i->Damage(UnitData->Damage, UnitData->DamageType, this);
	}
}