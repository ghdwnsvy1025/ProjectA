// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Popup/PAUIPopup_Inventory.h"

#include "ProjectA.h"
#include "Manager/PADataManager.h"
#include "Manager/PAItemManager.h"
#include "UI/PAUIBase_InventorySlot.h"

void UPAUIPopup_Inventory::NativeConstruct()
{
	Super::NativeOnInitialized();
	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);

	InventorySlot = CastChecked<UPAUIBase_InventorySlot>( CreateWidget(World,UPAUIBase_InventorySlot::StaticClass()));
	
}

