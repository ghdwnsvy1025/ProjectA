// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Data/PAItemTable.h"
#include "UI/PAUIBase.h"
#include "PAUIBase_InventorySubTypeSlot.generated.h"


UCLASS()
class PROJECTA_API UPAUIBase_InventorySubTypeSlot : public UPAUIBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	void SetItemType(EItemType type){ItemType=type;}
	void Init(EItemType Type);
	void Refresh();
	UFUNCTION()
	void OnVisibilityChangedEventFunc(ESlateVisibility SlateVisibility);
	
	UFUNCTION(BlueprintCallable, Category =Hovering)
	void ShowHoveringUI(const FName& ItemName, const FPAItemTable& ItemTable);
	
	UFUNCTION(BlueprintCallable, Category =Hovering)
	void HideHoveringUI(const class UPAItemButton* Button);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> MyVertical;

	EItemType ItemType;
	
	uint8 bIsInit : 1;
	
	uint8 bIsModified = 1;

	uint8 bIsHovering = 1;
	FOnVisibilityChangedEvent OnVisibilityChangedEvent;
};
