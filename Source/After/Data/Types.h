    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: Types.h                     //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "PaperFlipbook.h"

#include "Types.generated.h"

UENUM(BlueprintType)
enum class FDamageType : uint8
{
	Strike,
	Cut,
	Pierce,
	Poison,
	Radiation,
	Suffocation,
	Burn,

	Begin = Strike,
	End = Burn
};
inline void operator++(FDamageType& DamageType)
{
	DamageType = static_cast<FDamageType>(static_cast<int>(DamageType) + 1);
}

UENUM(BlueprintType)
enum class FDirection : uint8
{
	F,	// Forward
	R,	// Right
	B,	// Backward
	L,	// Left

	// !
	Begin = F,
	End = L
};
inline void operator++(FDirection& Direction)
{
	Direction = static_cast<FDirection>(static_cast<int>(Direction) + 1);
}

UENUM(BlueprintType)
enum class FEntityStatus : uint8
{
	Stay,
	Walk,
	Run,
	Swim,
	Attack,
	LongAttack,
	Death,
	Damage,
	Stone,
	Web,
	Special,

	// !
	Begin = Stay,
	End = Special
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