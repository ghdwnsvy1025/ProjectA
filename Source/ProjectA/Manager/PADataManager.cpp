// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/PADataManager.h"

#include "ProjectA.h"
#include "Data/PAUIClassTable.h"
#include "Engine/ObjectLibrary.h"

void UPADataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	bIsInitialize = false;
	
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UPADataManager::OnWorldInitialized);
}

void UPADataManager::OnWorldInitialized(UWorld* World, const UWorld::InitializationValues InitializationValues)
{
	if(bIsInitialize)
	{
		return;
	}
	
	LoadAllTables();
	
	bIsInitialize = true;
}

void UPADataManager::LoadAllTables()
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UDataTable::StaticClass(), false, false);
	CHECK_NULLPTR_RETURN(ObjectLibrary,);

	ObjectLibrary->LoadAssetsFromPath(TEXT("/Game/Data"));
	TArray<UDataTable*> DataTables;
	ObjectLibrary->GetObjects(DataTables);
	
	// 데이터 추가 시 작업
	for (auto& DataTable : DataTables)
	{
		UScriptStruct* RowStruct = DataTable->RowStruct;

		if(FPAUIClassTable::StaticStruct() == RowStruct)
		{
			LoadTable<FPAUIClassTable>(DataTable, UIClassTableData);
		}
		else if(FPAShopTable::StaticStruct() == RowStruct)
		{
			LoadTable<FPAShopTable>(DataTable, ShopTableData);
		}
	}
}