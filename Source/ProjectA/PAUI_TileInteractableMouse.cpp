// Fill out your copyright notice in the Description page of Project Settings.


#include "PAUI_TileInteractableMouse.h"

#include "ProjectA.h"
#include "Components/Button.h"

void UPAUI_TileInteractableMouse::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(TileButton)
	{
		TileButton->OnClicked.AddDynamic(this, &UPAUI_TileInteractableMouse::OnButtonClickedFunc);
		TileButton->OnHovered.AddDynamic(this,&UPAUI_TileInteractableMouse::OnButtonHoveredFunc);
		TileButton->OnUnhovered.AddDynamic(this,&UPAUI_TileInteractableMouse::OnButtonUnHoveredFunc);
		OriginalColor = ColorAndOpacity;
		SetOppacity(true);
		
	}
}

void UPAUI_TileInteractableMouse::OnButtonClickedFunc()
{
	PA_LOG(LogTest, Log, TEXT("Button Clicked"));

}

void UPAUI_TileInteractableMouse::OnButtonHoveredFunc()
{
	PA_LOG(LogTest, Log, TEXT("Button Hovered"));
	SetOppacity(false);

}

void UPAUI_TileInteractableMouse::OnButtonUnHoveredFunc()
{
	PA_LOG(LogTest, Log, TEXT("Button UnHovered"));
	SetOppacity(true);

}

void UPAUI_TileInteractableMouse::SetOppacity(bool IsZero)
{
	float Alpha = 0;
	if(IsZero)
	{
		Alpha =0;
	}
	else
	{
		Alpha=OriginalColor.A;
	}
	FLinearColor TransparentColor = FLinearColor(OriginalColor.R, OriginalColor.G, OriginalColor.B, Alpha);
	ColorAndOpacity = TransparentColor;
	SetColorAndOpacity(ColorAndOpacity);
	PA_LOG(LogTest, Log, TEXT("%f"), ColorAndOpacity.A);
}

