// Fill out your copyright notice in the Description page of Project Settings.


#include "PAGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Manager/PADataManager.h"
#include "Manager/PAInventoryManager.h"
#include "Manager/PAItemManager.h"
#include "Manager/PAShopManager.h"
#include "Manager/PAUIManager.h"
#include "Tag/PAGameplayTag.h"

void APAGameMode::BeginPlay()
{
	Super::BeginPlay();


}

void APAGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);

	World->GetSubsystem<UPADataManager>()->Init(World);
	World->GetSubsystem<UPAItemManager>()->Init(World);
	World->GetSubsystem<UPAShopManager>()->Init(World);
	World->GetGameInstance()->GetSubsystem<UPAInventoryManager>()->Init(World);
	
	UPAUIManager::Get().Init(GetWorld());
	
	FString LevelName = World->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	
	FString PreName = TEXT("UI.Scene.");
	LevelName = PreName + LevelName;
	
	UPAUIManager::Get().ShowScene(GetData(LevelName));
	UPAUIManager::Get().ShowPopup(PATAG_UI_POPUP_INVENTORY.GetTagName());
}
