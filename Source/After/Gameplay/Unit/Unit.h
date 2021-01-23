    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Unit.h                      //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "../../Data/DA_Database.h"

#include "Unit.generated.h"

UCLASS()
class AFTER_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	AUnit();

	virtual void Tick(float DeltaTime) override;

			/* APPEARANCE */

	void Select();
	void Unselect();

protected:
	virtual void BeginPlay() override;

			/* GENERAL */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FGameplayTag Id;

	const FUnitInfo* UnitData;

	UFUNCTION(BlueprintCallable)
	const FUnitInfo& GetUnitData() const;

			/* ATTACK */

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* Component1, AActor* Actor,
		UPrimitiveComponent* Component2, int32 Int, bool Bool, const FHitResult& HitResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* Component1, AActor* Actor, UPrimitiveComponent* Component2, int32 Int);

	UFUNCTION()
	void DamageForEntities();

			/* COMPONENTS */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* DamageBoxComponent;

private:
			/* TIMERS */

	TMap<class AEntity*, FTimerHandle> DamageTimers;

};
