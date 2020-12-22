    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // Lisence: GNU GPL v2.0              //
 //  File: Entity.cpp                  //
////////////////////////////////////////

#include "Entity.h"

#include "../../AfterGameModeBase.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	AAfterGameModeBase* AfterGameMode;
	// if the tag is valid and there are the world and the correct game mode
	if (Id.IsValid() && GetWorld() && (AfterGameMode = Cast<AAfterGameModeBase>(GetWorld()->GetAuthGameMode()), AfterGameMode))
	{
		EntityData = AfterGameMode->GetDatabase()->GetEntityData(Id);
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
