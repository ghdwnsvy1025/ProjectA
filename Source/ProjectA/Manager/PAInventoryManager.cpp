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
	UPAItemManager* ItemManager =World->GetSubsystem<UPAItemManager>();
	CHECK_NULLPTR_RETURN(ItemManager,);
	// To Do : Save 파일 Load해서 Map에 넣어야함

	// Weapon
	TMap<FName,FPAItemTable> WeaponTable;
	ItemManager->GetTable(EItemType::Weapon, WeaponTable);

	FInnerItemTable WeaponInnerTable;
	WeaponInnerTable.InnerMap = WeaponTable;
	ItemTables.Emplace(EItemType::Weapon, WeaponInnerTable);

	// To Do : Quality 채우기
	// Armor
	TMap<FName,FPAItemTable> ArmorTable;
	ItemManager->GetTable(EItemType::Armor, ArmorTable);

	FInnerItemTable ArmorInnerTable;
	ArmorInnerTable.InnerMap = ArmorTable;
	ItemTables.Emplace(EItemType::Armor, ArmorInnerTable);
}
