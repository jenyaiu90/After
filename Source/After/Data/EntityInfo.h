    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // Lisence: GNU GPL v2.0              //
 //  File: EntityInfo.h                //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "EntityInfo.generated.h"

USTRUCT(BlueprintType)
struct FEntityInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxHealth;
};