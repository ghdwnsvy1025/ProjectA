// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAItemButton.h"


UPAItemButton::UPAItemButton()
{
	OnHovered.AddDynamic(this,&UPAItemButton::CustomOnHoveredFunc);
	OnUnhovered.AddDynamic(this,&UPAItemButton::CustomOnUnHoveredFunc);
	OnClicked.AddDynamic(this,&UPAItemButton::CustomOnClickedFunc);
}

void UPAItemButton::CustomOnHoveredFunc()
{
	CustomOnHovered.Broadcast(MyItemName,MyItemTable);
}

void UPAItemButton::CustomOnUnHoveredFunc()
{
	CustomOnUnHovered.Broadcast(this);

}

void UPAItemButton::CustomOnClickedFunc()
{
	CustomOnClicked.Broadcast(MyItemTable);
}
