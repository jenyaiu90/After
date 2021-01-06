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

void ALast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ALast::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ALast::ZoomOut);
}

void ALast::BeginPlay()
{
	Super::BeginPlay();

	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, -90.f, 0.f));
}

void ALast::ZoomIn()
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(
		SpringArmComponent->TargetArmLength * 0.8f,
		200.f, 2000.f);
}

void ALast::ZoomOut()
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(
		SpringArmComponent->TargetArmLength * 1.25f,
		200.f, 2000.f);
}