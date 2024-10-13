// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Popup/PAUIPopup_DungeonEntrance.h"

#include "ProjectA.h"
#include "Components/Button.h"
#include "Manager/PAUIManager.h"

void UPAUIPopup_DungeonEntrance::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(EntranceBtn)
	{
		EntranceBtn->OnReleased.AddDynamic(this,&UPAUIPopup_DungeonEntrance::OnEntranceBtnClickedFunc);
	}
	if(ExitBtn)
	{
		ExitBtn->OnReleased.AddDynamic(this, &UPAUIPopup_DungeonEntrance::OnExitBtnClickedFunc);
	}
}

void UPAUIPopup_DungeonEntrance::OnEntranceBtnClickedFunc()
{
	PA_LOG(LogTest,Log,TEXT("Entrance Dungeon!"));
}

void UPAUIPopup_DungeonEntrance::OnExitBtnClickedFunc()
{
	UPAUIManager::Get().ClosePopup();
}
