// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/PAShopManager.h"

#include "PADataManager.h"
#include "Data/PAItemTable.h"
#include "Tag/PAGameplayTag.h"

void UPAShopManager::Init(UWorld* World)
{
	CHECK_NULLPTR_RETURN(World,);
	// Data Load
	TMap<FName, FPAShopTable> GranTable;
	if(!World->GetSubsystem<UPADataManager>()->LoadData(TEXT("PAShopGranTable"), GranTable))
	{
		PA_LOG(LogTest,Warning,TEXT("Failed To Load GranTableData"));
	}
	FInnerShopTable InnerGranTable;
	InnerGranTable.InnerMap = GranTable;
	ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_GRAN.GetTagName(), InnerGranTable);
	
	// Data Load
	TMap<FName, FPAShopTable> TromboTable;
	if(!World->GetSubsystem<UPADataManager>()->LoadData(TEXT("PAShopTromboTable"), TromboTable))
	{
		PA_LOG(LogTest,Warning,TEXT("Failed To Load TromboTableData"));

	}
	FInnerShopTable InnerTromboTable;
	InnerTromboTable.InnerMap = TromboTable;
	ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_TROMBO.GetTagName(), InnerTromboTable);

	
	PA_LOG(LogTest,Log,TEXT("ShopManger Load Complete!"));
}

void UPAShopManager::BuyItem(FName TagName, int32 Index)
{
	FInnerShopTable ShopTable = ShopTables[TagName];

	
}

void UPAShopManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// Data Load
	// TMap<FName, FPAShopTable> GranTable;
	// InWorld.GetSubsystem<UPADataManager>()->LoadData(TEXT("PAShopGranTable"), GranTable);
	// ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_GRAN.GetTagName(), GranTable);
	//
	// // Data Load
	// TMap<FName, FPAShopTable> TromboTable;
	// InWorld.GetSubsystem<UPADataManager>()->LoadData(TEXT("PAShopTromboTable"), TromboTable);
	// ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_TROMBO.GetTagName(), TromboTable);
}
