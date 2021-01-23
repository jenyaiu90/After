    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Last.cpp                    //
////////////////////////////////////////

#include "Last.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/BoxComponent.h"

ALast::ALast() :
	AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ALast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Energy: %f"), Energy));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
}

void ALast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

void ALast::BeginPlay()
{
	Super::BeginPlay();

	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, -90.f, 0.f));
}