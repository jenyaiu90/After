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

			/* MOVEMENT */

	void StartRunning();
	void StopRunning();
	void MoveX(float Val);
	void MoveY(float Val);

			/* STATS */

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Damage(float Value, FDamageType DamageType, AActor* FromWho);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Death(AActor* Murderer);

			/* APPEARANCE */

	void Select();
	void Unselect();

protected:
	virtual void BeginPlay() override;

			/* GENERAL */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FGameplayTag Id;

	const FEntityInfo* EntityData;

	UFUNCTION(BlueprintCallable)
	const FEntityInfo& GetEntityData() const;

			/* STATS */

	UPROPERTY(BlueprintReadOnly, Category = "General")
	bool bIsDead;

	UFUNCTION()
	void CalculateStats();

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float Energy;

			/* ATTACK */

	UFUNCTION(BlueprintCallable)
	bool MeleeAttack(AEntity* Attacked);

			/* COMPONENTS */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

			/* MOVING */

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	bool bIsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	float MovementX;

	UPROPERTY(BlueprintReadOnly, Category = "Moving")
	float MovementY;

private:
			/* TIMERS */

	FTimerHandle StatsTimer;
	FTimerHandle TextureTimer;

			/* STATS */

	void Damage(float Value, FDamageType DamageType);	// Shouldn't be called
	void Death();										//		directly.

			/* APPEARANCE */

	FDirection CurrentDirection;	// Current texture direction
	FEntityStatus CurrentStatus;	// Current texture status
	bool bIsTextureBlocked;			// Texture is not looping

	UFUNCTION()
	void UnblockTexture();			// Unblocks texture
};
