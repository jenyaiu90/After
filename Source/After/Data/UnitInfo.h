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
			/* APPEARANCE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeX = 1;					// Unit's horizontal size

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeY = 1;					// Unit's vertical size
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	UPaperSprite* Sprite;			// Unit's sprite
};