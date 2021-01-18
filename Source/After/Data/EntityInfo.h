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
	float MaxHealth = 100.f;							// The greatest possible value of health

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TMap<FDamageType, float> DamageResist;				// Damage is multiples by this value; <1 - resist; >1 - vulnerability

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxEnergy = 100.f;							// The greatest possible value of energy

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float EnergySpeed = 10.f;							// Energy decreasing per tick * delta while running

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float EnergyRegenerationSpeed = 5.f;				// Energy increasing per second while resting

			/* ATTACK */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float MeleeDamage = 0.f;							// The damage that entity can cause; 0 - can't attack (melee)

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float MeleeRadius = 100.f;							// The radius where entity can attack

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FDamageType MeleeDamageType = FDamageType::Strike;	// The damage type for melee attack

			/* MOVING */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float WalkSpeed = 50.f;								// Entity offset per tick * delta while walking

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float RunSpeed = 75.f;								// Entity offset per tick * delta while running

			/* APPEARANCE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeX = 1;										// Entity's horizontal size

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeY = 1;										// Entity's vertical size

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	TMap<FEntityStatus, FEntityFlipbooks> Flipbooks;	// The flipbooks for entity
	
};