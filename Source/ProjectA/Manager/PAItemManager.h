// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectA.h"
#include "Data/PAItemTable.h"
#include "Subsystems/WorldSubsystem.h"
#include "PAItemManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAItemManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void Init(UWorld* World);

	void GetAllTable(TMap<int32, FPAItemTable>& OutTable) const
	{
		OutTable = ItemTables;
	}

	void GetTable(int32 ItemIndex, FPAItemTable& OutTable) const
	{
		if(ItemTables.Contains(ItemIndex))
		{
			OutTable = ItemTables[ItemIndex];
		}
		else
		{
			PA_LOG(LogTest,Log,TEXT("Failed To Get ItemTable Index : %d"), ItemIndex);
		}
	}
	
	UTexture2D* GetTexture(FName& TextureName) const
	{
		if (Textures.Find(TextureName))
		{
			return Textures[TextureName];
		}
		else
		{
			return NewObject<UTexture2D>();
		}
	}

private:
	void LoadItem(EItemType ItemType, FName& BPTableName);
	void LoadTexture(EItemType ItemType, const TMap<FName, FPAItemTable>& ItemTable);

private:
	// UPROPERTY(EditAnywhere, Category = ItemManager)
	// TMap<EItemType,FInnerItemTable> ItemTables;

	UPROPERTY(EditAnywhere, Category = ItemManager)
	TMap<int32, FPAItemTable> ItemTables;

	UPROPERTY(EditAnywhere, Category = ItemManager)
	TMap<FName, TObjectPtr<UTexture2D>> Textures;
	// Portion
	// Scroll
};
