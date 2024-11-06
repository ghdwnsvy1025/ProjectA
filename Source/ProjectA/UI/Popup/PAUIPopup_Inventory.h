// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Popup/PAUIPopup.h"
#include "PAUIPopup_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIPopup_Inventory : public UPAUIPopup
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, Category = Inventory)
	TObjectPtr<class UPAUIBase_InventorySlot> InventorySlot;
};