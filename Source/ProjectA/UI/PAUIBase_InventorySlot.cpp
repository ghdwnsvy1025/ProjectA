// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAUIBase_InventorySlot.h"

#include "PAUIBase_InventorySubTypeSlot.h"
#include "ProjectA.h"

void UPAUIBase_InventorySlot::NativeOnInitialized()
{
	PA_LOG(LogTest, Log, TEXT("Create Slot"));

	Super::NativeOnInitialized();
	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);

	// UPAUIBase_InventorySubTypeSlot* AllSlot = CastChecked<UPAUIBase_InventorySubTypeSlot>(
	// 	CreateWidget(World, UPAUIBase_InventorySubTypeSlot::StaticClass()));
	//
	// AllSlot->Init(EItemType::All);
	// InventorySubTypeSlot.Emplace(EItemType::All, AllSlot);
	//
	if (WBP_InventorySlotAll)
	{
		WBP_InventorySlotAll->Init(EItemType::All);
		InventorySubTypeSlot.Emplace(EItemType::All, WBP_InventorySlotAll);
	}
	if (WBP_InventorySlotWeapon)
	{
		WBP_InventorySlotWeapon->Init(EItemType::Weapon);
		InventorySubTypeSlot.Emplace(EItemType::Weapon, WBP_InventorySlotWeapon);
	}
	if (WBP_InventorySlotArmor)
	{
		WBP_InventorySlotArmor->Init(EItemType::Armor);

		InventorySubTypeSlot.Emplace(EItemType::Armor, WBP_InventorySlotArmor);
	}
	if (WBP_InventorySlotPortion)
	{
		WBP_InventorySlotPortion->Init(EItemType::Portion);

		InventorySubTypeSlot.Emplace(EItemType::Portion, WBP_InventorySlotPortion);
	}
	if (WBP_InventorySlotScroll)
	{
		WBP_InventorySlotScroll->Init(EItemType::Scroll);

		InventorySubTypeSlot.Emplace(EItemType::Scroll, WBP_InventorySlotScroll);
	}
	// TObjectPtr<UPAUIBase_InventorySubTypeSlot> Weaponslot = CastChecked<UPAUIBase_InventorySubTypeSlot>(
	// 	CreateWidget(World, UPAUIBase_InventorySubTypeSlot::StaticClass()));
	//
	// Weaponslot->Init(EItemType::Weapon);
	// InventorySubTypeSlot.Emplace(EItemType::Weapon, Weaponslot);
	//
	//
	// UPAUIBase_InventorySubTypeSlot* ArmorSlot = CastChecked<UPAUIBase_InventorySubTypeSlot>(
	// 	CreateWidget(World, UPAUIBase_InventorySubTypeSlot::StaticClass()));
	// ArmorSlot->Init(EItemType::Armor);
	// InventorySubTypeSlot.Emplace(EItemType::Armor, ArmorSlot);
	//
	//
	// UPAUIBase_InventorySubTypeSlot* PortionSlot = CastChecked<UPAUIBase_InventorySubTypeSlot>(
	// 	CreateWidget(World, UPAUIBase_InventorySubTypeSlot::StaticClass()));
	//
	// PortionSlot->Init(EItemType::Portion);
	// InventorySubTypeSlot.Emplace(EItemType::Portion, PortionSlot);
	//
	// UPAUIBase_InventorySubTypeSlot* ScrollSlot = CastChecked<UPAUIBase_InventorySubTypeSlot>(
	// 	CreateWidget(World, UPAUIBase_InventorySubTypeSlot::StaticClass()));
	//
	// ScrollSlot->Init(EItemType::Scroll);
	// InventorySubTypeSlot.Emplace(EItemType::Scroll, ScrollSlot);

	if (AllBtn)
	{
		AllBtn->OnReleased.AddDynamic(this, &UPAUIBase_InventorySlot::SwitchSubAllSlot);
	}
	if (WeaponBtn)
	{
		WeaponBtn->OnReleased.AddDynamic(this, &UPAUIBase_InventorySlot::SwitchSubWeaponSlot);
	}
	if (ArmorBtn)
	{
		ArmorBtn->OnReleased.AddDynamic(this, &UPAUIBase_InventorySlot::SwitchSubArmorSlot);
	}
	if (PortionBtn)
	{
		PortionBtn->OnReleased.AddDynamic(this, &UPAUIBase_InventorySlot::SwitchSubPortionSlot);
	}
	if (ScrollBtn)
	{
		ScrollBtn->OnReleased.AddDynamic(this, &UPAUIBase_InventorySlot::SwitchSubScrollSlot);
	}
	// if (ItemSwitcher)
	// {
	// 	// ItemSwitcher->AddChild(AllSlot);
	// 	ItemSwitcher->AddChild(Weaponslot);
	// 	ItemSwitcher->AddChild(ArmorSlot);
	// 	ItemSwitcher->AddChild(PortionSlot);
	// 	ItemSwitcher->AddChild(ScrollSlot);
	// }
}

void UPAUIBase_InventorySlot::SwitchSubAllSlot()
{
	ItemSwitcher->SetActiveWidgetIndex((int)EItemType::All);
}

void UPAUIBase_InventorySlot::SwitchSubWeaponSlot()
{
	ItemSwitcher->SetActiveWidgetIndex((int)EItemType::Weapon);
}

void UPAUIBase_InventorySlot::SwitchSubArmorSlot()
{
	ItemSwitcher->SetActiveWidgetIndex((int)EItemType::Armor);
}

void UPAUIBase_InventorySlot::SwitchSubPortionSlot()
{
	ItemSwitcher->SetActiveWidgetIndex((int)EItemType::Portion);
}

void UPAUIBase_InventorySlot::SwitchSubScrollSlot()
{
	ItemSwitcher->SetActiveWidgetIndex((int)EItemType::Scroll);
}
