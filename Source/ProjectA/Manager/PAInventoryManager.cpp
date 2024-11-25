// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/PAInventoryManager.h"

#include "PADataManager.h"
#include "PAItemManager.h"
#include "ProjectA.h"

#include "Blueprint/UserWidget.h"
#include "UI/PAUIBase_InventorySlot.h"
#include "UI/Popup/PAUIPopup_Inventory.h"

void UPAInventoryManager::Init(UWorld* World)
{
	CHECK_NULLPTR_RETURN(World,);
	UPAItemManager* ItemManager = World->GetSubsystem<UPAItemManager>();
	CHECK_NULLPTR_RETURN(ItemManager,);
	// To Do : Save 파일 Load해서 Map에 넣어야함

	TMap<int32, FPAItemTable> TempItemTables;
	ItemManager->GetAllTable(TempItemTables);

	FInnerItemTable WeaponInnerItemTable;
	FInnerItemTable ArmorInnerTable;
	FInnerItemTable PortionInnerItemTable;
	FInnerItemTable ScrollInnerItemTable;

	for (auto Pair : TempItemTables)
	{
		EItemType ItemType = Pair.Value.ItemType;
		int32 Index = Pair.Key;
		FPAItemTable ItemTable = Pair.Value;

		switch (ItemType)
		{
		case EItemType::Weapon:
			WeaponInnerItemTable.InnerMap.Emplace(Index, ItemTable);
			break;
		case EItemType::Armor:
			ArmorInnerTable.InnerMap.Emplace(Index, ItemTable);
			break;
		case EItemType::Portion:
			PortionInnerItemTable.InnerMap.Emplace(Index, ItemTable);
			break;
		case EItemType::Scroll:
			ScrollInnerItemTable.InnerMap.Emplace(Index, ItemTable);
			break;
		default:
			break;
		}
	}
	ItemTables.Emplace(EItemType::Weapon, WeaponInnerItemTable);
	ItemTables.Emplace(EItemType::Armor, ArmorInnerTable);
	ItemTables.Emplace(EItemType::Portion, PortionInnerItemTable);
	ItemTables.Emplace(EItemType::Scroll, ScrollInnerItemTable);
}
