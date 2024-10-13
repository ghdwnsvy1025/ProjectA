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
	OnButtonDelgate.Broadcast();
}

void UPAUI_TileInteractableMouse::OnButtonHoveredFunc()
{
	SetOppacity(false);
}

void UPAUI_TileInteractableMouse::OnButtonUnHoveredFunc()
{
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

}

// 음 PATile -> TileInterac : 이거는 모든 타일마다 공통적인 거라서 하나만 필요해.
// Tag를 BP_PATile에 설정 -> TileInterac에 델리게이트 생성 후 클릭시 발동 -> 델리게이트에 PA함수가 연동되어 있어 함수 발동
// -> PATile의 Tag를 가지고 있는 GA 발동 -> ??
// 아니면 TileInteraction에서 직접 UI호출?? 상관 없음.
// 어짜피 Tag를 통해서 그거에 맞는 UI를 호출해야함.
// Tag를 통해 UI를 찾아서 Show한다?? 이거 였잖아. 현재 Name과 UI가 묶여있느니, Tag와 Name을 묶으면 되겠네.
// Tag == FGamePlayTag.GetTagName == FName