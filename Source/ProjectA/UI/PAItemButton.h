// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Data/PAItemTable.h"
#include "PAItemButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCustomOnHovered, const FName&, ItemName, const FPAItemTable&, ItemTable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomOnUnHovered,const UPAItemButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomOnClicked,const FPAItemTable&, ItemTable);

UCLASS()
class PROJECTA_API UPAItemButton : public UButton
{
	GENERATED_BODY()

public:
	UPAItemButton();

public:
	void Init(const FName& ItemName, const FPAItemTable& ItemTable)
	{
		MyItemName = ItemName;
		MyItemTable= ItemTable;
	}
	UFUNCTION()
	void CustomOnHoveredFunc();
	UFUNCTION()
	void CustomOnUnHoveredFunc();
	UFUNCTION()
	void CustomOnClickedFunc();

public:
	UPROPERTY()
	FCustomOnHovered CustomOnHovered;
	UPROPERTY()
	FCustomOnUnHovered CustomOnUnHovered;
	UPROPERTY()
	FCustomOnClicked CustomOnClicked;
	UPROPERTY()
	FName MyItemName;

	UPROPERTY()
	FPAItemTable MyItemTable;
};