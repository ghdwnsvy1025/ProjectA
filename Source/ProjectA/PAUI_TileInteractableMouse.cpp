// Fill out your copyright notice in the Description page of Project Settings.


#include "PAUI_TileInteractableMouse.h"

#include "ProjectA.h"
#include "Components/Button.h"

void UPAUI_TileInteractableMouse::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnVisibilityChanged.AddDynamic(this, &UPAUI_TileInteractableMouse::OnVisibilityChangedFunc);
	if(TileButton)
	{
		TileButton->OnClicked.AddDynamic(this, &UPAUI_TileInteractableMouse::OnButtonClickedFunc);
	}
	SetVisibility(ESlateVisibility::Visible);

}

void UPAUI_TileInteractableMouse::OnVisibilityChangedFunc(ESlateVisibility SlateVisibility)
{
	// PA_LOG(LogTest, Log, TEXT("Visiblity Change"));
}

void UPAUI_TileInteractableMouse::OnButtonClickedFunc()
{
	PA_LOG(LogTest, Log, TEXT("Button Clicked"));

}

