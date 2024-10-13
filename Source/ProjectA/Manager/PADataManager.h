// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectA.h"
#include "Data/PADataTable.h"
#include "Data/PAShopTable.h"
#include "Data/PAUIClassTable.h"
#include "PADataManager.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTA_API UPADataManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	template <typename T>
	const TMap<FName, T>& GetData(FName TableName) const;

private:
	void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues InitializationValues);
	void LoadAllTables();
	template <typename T>
	void LoadTable(UDataTable* DataTable, TMap<FName, T>& OutTableData);

private:
	uint8 bIsInitialize : 1;
	
	TMap<FName, FPAShopTable> ShopTableData;
	TMap<FName, FPAUIClassTable> UIClassTableData;
};

// 데이터 추가 시 작업
template <typename T>
const TMap<FName, T>& UPADataManager::GetData(FName TableName) const
{
	if constexpr (TIsSame<T, FPAUIClassTable>::Value)
	{
		return UIClassTableData;
	}
	else if constexpr (TIsSame<T, FPAShopTable>::Value)
	{
		return ShopTableData;  
	}
	else
	{
		return TMap<FName,T>();
	}
}

template <typename T>
void UPADataManager::LoadTable(UDataTable* DataTable, TMap<FName, T>& OutTableData)
{
	CHECK_NULLPTR_RETURN(DataTable,);
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (auto& Pair : RowMap)
	{
		T* RowData = reinterpret_cast<T*>(Pair.Value);
		if (RowData)
		{
			OutTableData.Emplace(Pair.Key, *RowData);
		}
	}
}
