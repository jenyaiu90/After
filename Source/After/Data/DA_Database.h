    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // Lisence: GNU GPL v2.0              //
 //  File: DA_Database.h               //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "EntityInfo.h"

#include "DA_Database.generated.h"

UCLASS()
class AFTER_API UDA_Database : public UDataAsset
{
	GENERATED_BODY()
	
protected:
			/* ENTITY */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Entity")
	TMap<FGameplayTag, FEntityInfo> EntityData;

public:
			/* ENTITY */
	UFUNCTION(BlueprintCallable)
	FEntityInfo GetEntityData(const FGameplayTag Tag) const;
};
