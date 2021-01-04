    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: EntityInfo.h                //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "PaperFlipbook.h"

#include "EntityInfo.generated.h"

UENUM(BlueprintType)
enum class FDirection : uint8
{
	F,	// Forward
	FR,	// Forward-right
	R,	// Right
	BR,	// Backward-right
	B,	// Backward
	BL,	// Backward-left
	L,	// Left
	FL,	// Forward-left

	// !
	BEGIN = F,
	END = FL
};
inline void operator++(FDirection& Direction)
{
	Direction = static_cast<FDirection>(static_cast<int>(Direction) + 1);
}

UENUM(BlueprintType)
enum class FEntityStatus : uint8
{
	STAY,
	WALK,
	RUN,
	SWIM,
	ATTACK,
	LONG_ATTACK,
	DEATH,
	DAMAGE,
	STONE,
	WEB,
	SPECIAL,

	// !
	BEGIN = STAY,
	END = SPECIAL
};
inline void operator++(FEntityStatus& Status)
{
	Status = static_cast<FEntityStatus>(static_cast<int>(Status) + 1);
}

USTRUCT(BlueprintType)
struct FEntityFlipbooks
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Flipbook")
	TMap<FDirection, UPaperFlipbook*> Flipbooks;	// Flipbooks for directions
};

USTRUCT(BlueprintType)
struct FEntityInfo
{
	GENERATED_USTRUCT_BODY()

public:
	/* STATS */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxHealth;

	/* MOVING */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	float RunSpeed;

	/* APPEARANCE */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	int SizeY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
	TMap<FEntityStatus, FEntityFlipbooks> Flipbooks;	// The flipbooks for statuses
	
};