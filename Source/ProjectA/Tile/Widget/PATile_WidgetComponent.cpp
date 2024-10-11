// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/Widget/PATile_WidgetComponent.h"
#include "Blueprint/UserWidget.h"

void UPATile_WidgetComponent::InitWidget()
{
	Super::InitWidget();

	// SetVisibility(true);
}

void UPATile_WidgetComponent::ShowWidget()
{
	if(GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void UPATile_WidgetComponent::HiddenWidget()
{
	if(GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}
