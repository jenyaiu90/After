    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: EntityInfo.h                //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "Types.h"

#include "EntityInfo.generated.h"

USTRUCT(BlueprintType)
struct FEntityInfo
{
	GENERATED_USTRUCT_BODY()

public:
			/* STATS */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TMap<FDamageType, float> DamageResist;	// Damage is multiples by this value; <1 - resist; >1 - vulnerability

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxEnergy = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float EnergySpeed = 10.f;	// Per tick

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float EnergyRegenerationSpeed = 5.f;	// Per second

			/* MOVING */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float WalkSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float RunSpeed = 75.f;

			/* APPEARANCE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeX = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeY = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	TMap<FEntityStatus, FEntityFlipbooks> Flipbooks;	// The flipbooks for statuses
	
};