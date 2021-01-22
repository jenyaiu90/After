    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: DA_Database.cpp             //
////////////////////////////////////////

#include "DA_Database.h"

void UDA_Database::Check()
{

// Checking entity debug flipbooks
	for (FDirection i = FDirection::Begin; i <= FDirection::End; ++i)
	{
		if (!EntityDebugFlipbooks.Contains(i) || !EntityDebugFlipbooks[i])
		{
			UE_LOG(LogTemp, Error, TEXT("Entities' debug textures weren't found!"));
		}
	}

// Checking entity data
	TArray<FGameplayTag> Keys;
	EntityData.GetKeys(Keys);
	for (FGameplayTag i : Keys)
	{
// Checking damage resist
		bool HasResist = true;
		for (FDamageType j = FDamageType::Begin; j <= FDamageType::End; ++j)
		{
			if (!EntityData[i].DamageResist.Contains(j))
			{
				EntityData[i].DamageResist.Add(j, 1.f);
				HasResist = false;
			}
		}
		if (!HasResist)
		{
			UE_LOG(LogTemp, Warning, TEXT("There are no damage resist value for the entity %s"), *i.ToString());
		}

// Checking entity flipbooks
		bool HasTexture = true;
		for (FEntityStatus j = FEntityStatus::Begin; j <= FEntityStatus::End; ++j)
		{
			if (!EntityData[i].Flipbooks.Contains(j))
			{
				EntityData[i].Flipbooks.Add(j, FEntityFlipbooks());
			}

			for (FDirection k = FDirection::Begin; k <= FDirection::End; ++k)
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
			UE_LOG(LogTemp, Warning, TEXT("There are no textures for the entity %s"), *i.ToString());
		}
	}
}

const FEntityInfo& UDA_Database::GetEntityData(const FGameplayTag Tag) const
{
	if (!EntityData.Contains(Tag))
	{
		UE_LOG(LogTemp, Fatal, TEXT("Database doesn't contain data about entity %s"), *Tag.ToString());
	}
	return EntityData[Tag];
}

TMap<FDirection, UPaperFlipbook*> UDA_Database::GetEntityDebugFlipbooks() const
{
	return EntityDebugFlipbooks;
}

const FUnitInfo& UDA_Database::GetUnitData(const FGameplayTag Tag) const
{
	if (!UnitData.Contains(Tag))
	{
		UE_LOG(LogTemp, Fatal, TEXT("Database doesn't contain data about unit %s"), *Tag.ToString());
	}
	return UnitData[Tag];
}