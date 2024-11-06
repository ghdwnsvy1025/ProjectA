// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PAItemTable.h"
#include "UObject/NoExportTypes.h"
#include "PAInventoryManager.generated.h"


UCLASS()
class PROJECTA_API UPAInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Init(UWorld* World);
	bool GetTable(EItemType ItemType, FInnerItemTable& InnerTable) 
	{
		if (!ItemTables.Find(ItemType))
		{
			return  false;
		}
		else
		{
			InnerTable = ItemTables[ItemType];
			return  true;
		}
	}
	int GetItemQuantity(FName Name)
	{
		if(!Quantity.Find(Name))
			return 0;
		
		return  Quantity[Name];
	}
private:
	UPROPERTY(EditAnywhere, Category = InventoryManager)
	TObjectPtr<class UPAUIPopup_Inventory> Inventory;
	
	UPROPERTY(EditAnywhere, Category = InventoryManager)
	TMap<EItemType, FInnerItemTable> ItemTables;
	
	UPROPERTY(EditAnywhere, Category = ItemManager)
	TMap<FName, int> Quantity;
	
};
