// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Data/PAItemTable.h"
#include "UI/Popup/PAUIPopup.h"
#include "PAUIBase_InventorySlot.generated.h"

class UPAUIBase_InventorySubTypeSlot;
/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIBase_InventorySlot : public UPAUIPopup
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void SwitchSubAllSlot();

	UFUNCTION()
	void SwitchSubWeaponSlot();

	UFUNCTION()
	void SwitchSubArmorSlot();
	
	UFUNCTION()
	void SwitchSubPortionSlot();
	
	UFUNCTION()
	void SwitchSubScrollSlot();
	
private:
	UPROPERTY(EditAnywhere, Category = Inventory)
	TMap<EItemType, TObjectPtr<class UPAUIBase_InventorySubTypeSlot>> InventorySubTypeSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> ItemSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AllBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> WeaponBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ArmorBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PortionBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ScrollBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPAUIBase_InventorySubTypeSlot> WBP_InventorySlotAll;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPAUIBase_InventorySubTypeSlot> WBP_InventorySlotWeapon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPAUIBase_InventorySubTypeSlot> WBP_InventorySlotArmor;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPAUIBase_InventorySubTypeSlot> WBP_InventorySlotPortion;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPAUIBase_InventorySubTypeSlot> WBP_InventorySlotScroll;
	
};
