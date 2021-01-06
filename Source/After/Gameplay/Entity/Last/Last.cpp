    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Last.cpp                    //
////////////////////////////////////////

#include "Last.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ALast::ALast() :
	AEntity()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ALast::BeginPlay()
{
	Super::BeginPlay();

	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, -90.f, 0.f));
}