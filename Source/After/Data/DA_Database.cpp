    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // Lisence: GNU GPL v2.0              //
 //  File: DA_Database.cpp             //
////////////////////////////////////////

#include "DA_Database.h"

FEntityInfo UDA_Database::GetEntityData(const FGameplayTag Tag) const
{
	return EntityData.Contains(Tag) ? EntityData[Tag] : FEntityInfo();
}