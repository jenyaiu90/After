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

			/* COMPONENTS */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

private:
};
