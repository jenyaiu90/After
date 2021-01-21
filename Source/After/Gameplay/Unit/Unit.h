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

protected:
	virtual void BeginPlay() override;

			/* GENERAL */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FGameplayTag Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	FUnitInfo UnitData;

			/* COMPONENTS */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComponent;

public:
	virtual void Tick(float DeltaTime) override;

};
