    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: DA_Database.h               //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "EntityInfo.h"
#include "UnitInfo.h"

#include "DA_Database.generated.h"

UCLASS()
class AFTER_API UDA_Database : public UDataAsset
{
	GENERATED_BODY()
	
protected:
			/* ENTITY */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Entity")
	TMap<FGameplayTag, FEntityInfo> EntityData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Entity")
	TMap<FDirection, UPaperFlipbook*> EntityDebugFlipbooks;

			/* UNIT */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Unit")
	TMap<FGameplayTag, FUnitInfo> UnitData;

public:
	UFUNCTION()
	void Check();

			/* ENTITY */

	UFUNCTION(BlueprintCallable)
	const FEntityInfo& GetEntityData(const FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable)
	TMap<FDirection, UPaperFlipbook*> GetEntityDebugFlipbooks() const;

			/* UNIT */

	UFUNCTION(BlueprintCallable)
	const FUnitInfo& GetUnitData(const FGameplayTag Tag) const;
};
