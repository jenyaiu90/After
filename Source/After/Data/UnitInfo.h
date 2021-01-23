    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: UnitInfo.h                  //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "Types.h"

#include "UnitInfo.generated.h"

USTRUCT(BlueprintType)
struct FUnitInfo
{
	GENERATED_USTRUCT_BODY()

public:
			/* DAMAGE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FDamageType DamageType = FDamageType::Strike;	// Damage type

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float Damage = 0.f;								// Damage for entities per second (0 - no damage)

			/* APPEARANCE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeX = 1;									// Unit's horizontal size

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeY = 1;									// Unit's vertical size
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	UPaperSprite* Sprite;							// Unit's sprite
};