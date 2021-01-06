    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Entity.h                    //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "../../Data/DA_Database.h"

#include "Entity.generated.h"

UCLASS()
class AFTER_API AEntity : public APawn
{
	GENERATED_BODY()

public:
	AEntity();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/* GENERAL */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FGameplayTag Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	FEntityInfo EntityData;

	/* STATS */

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float Health;

	/* COMPONENTS */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

	/* MOVING */

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	bool bIsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	int MovementX;

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	int MovementY;

private:

	/* APPEARANCE */

	FDirection CurrentDirection;	// Current texture direction

	FEntityStatus CurrentStatus;	// Current texture status
};
