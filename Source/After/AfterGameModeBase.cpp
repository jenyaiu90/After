    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: DA_Database.h               //
////////////////////////////////////////

#include "AfterGameModeBase.h"

void AAfterGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	Database->Check();
}

UDA_Database* AAfterGameModeBase::GetDatabase() const
{
	return Database;
}