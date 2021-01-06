    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Last.h                      //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "../Entity.h"

#include "Last.generated.h"

UCLASS()
class AFTER_API ALast : public AEntity
{
	GENERATED_BODY()
	
public:
	ALast();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/* COMPONENTS */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent;

private:
	/* INPUT */
	void ZoomIn();
	void ZoomOut();
};