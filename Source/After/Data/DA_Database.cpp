    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: DA_Database.cpp             //
////////////////////////////////////////

#include "DA_Database.h"

void UDA_Database::Check()
{
// Checking entity debug flipbooks
	for (FDirection i = FDirection::BEGIN; i <= FDirection::END; ++i)
	{
		if (!EntityDebugFlipbooks.Contains(i) || !EntityDebugFlipbooks[i])
		{
			UE_LOG(LogTemp, Error, TEXT("Entities' debug textures weren't found!"));
		}
	}

// Checking entity flipbooks
	TArray<FGameplayTag> Keys;
	EntityData.GetKeys(Keys);
	for (FGameplayTag i : Keys)
	{
		bool HasTexture = true;
		for (FEntityStatus j = FEntityStatus::BEGIN; j <= FEntityStatus::END; ++j)
		{
			if (!EntityData[i].Flipbooks.Contains(j))
			{
				EntityData[i].Flipbooks.Add(j, FEntityFlipbooks());
			}

			for (FDirection k = FDirection::BEGIN; k <= FDirection::END; ++k)
			{
				if (!EntityData[i].Flipbooks[j].Flipbooks.Contains(k) || !EntityData[i].Flipbooks[j].Flipbooks[k])
				{
					EntityData[i].Flipbooks[j].Flipbooks.Add(k, EntityDebugFlipbooks[k]);
					HasTexture = false;
				}
			}
		}
		if (!HasTexture)
		{
			UE_LOG(LogTemp, Warning, TEXT("There are no textures for the entity %s"), *i.ToString())
		}
	}
}

FEntityInfo UDA_Database::GetEntityData(const FGameplayTag Tag) const
{
	return EntityData.Contains(Tag) ? EntityData[Tag] : FEntityInfo();
}

TMap<FDirection, UPaperFlipbook*> UDA_Database::GetEntityDebugFlipbooks() const
{
	return EntityDebugFlipbooks;
}