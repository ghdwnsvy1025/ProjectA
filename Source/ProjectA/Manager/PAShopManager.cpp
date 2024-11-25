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
	TMap<int32, FPAShopTable> GranInnerMap;
	for(auto Pair : GranTable)
	{
		int32 Index = Pair.Value.DataIndex;
		GranInnerMap.Emplace(Index,Pair.Value);
	}

	FInnerShopTable InnerGranTable;
	InnerGranTable.InnerMap = GranInnerMap;
	ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_GRAN.GetTagName(), InnerGranTable);
	
	// Data Load
	TMap<FName, FPAShopTable> TromboTable;
	if(!World->GetSubsystem<UPADataManager>()->LoadData(TEXT("PAShopTromboTable"), TromboTable))
	{
		PA_LOG(LogTest,Warning,TEXT("Failed To Load TromboTableData"));

	}
	TMap<int32, FPAShopTable> TromboInnerMap;
	for(auto Pair : TromboTable)
	{
		int32 Index = Pair.Value.DataIndex;
		TromboInnerMap.Emplace(Index,Pair.Value);
	}
	FInnerShopTable InnerTromboTable;
	InnerTromboTable.InnerMap = TromboInnerMap;
	ShopTables.Emplace(PATAG_INTERACTABLEOBJECT_SHOP_TROMBO.GetTagName(), InnerTromboTable);

	
	PA_LOG(LogTest,Log,TEXT("ShopManger Load Complete!"));
}


void UPAShopManager::BuyItem(const FName& ShopName, const FPAItemTable& ItemTable)
{
	
	// 1. Inven의 돈 확인 후, 돈이 충분하면 구입

	if(ShopTables.Contains(ShopName))
	{
		FInnerShopTable InnerShopTable = ShopTables[ShopName];
		
		
	}
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
