    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: DA_Database.h               //
////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "Data/DA_Database.h"

#include "AfterGameModeBase.generated.h"

UCLASS()
class AFTER_API AAfterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
	UDA_Database* Database; // The data asset with data about all gameplay objects

public:
	UFUNCTION(BlueprintCallable, Category = "Database")
	UDA_Database* GetDatabase() const; // Returns the database
};
