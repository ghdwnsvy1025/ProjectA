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

	// template <typename T>
	// const TMap<FName, T>& GetData() const;
	template <typename T>
	bool LoadData(FName BPTableName, TMap<FName, T>& OutTableData);
	void Init(UWorld* World);

private:
	void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues InitializationValues);
	void LoadAllTables(UWorld* World);
	template <typename T>
	void LoadTable(UDataTable* DataTable, TMap<FName, T>& OutTableData);

private:
	uint8 bIsInitialize : 1;
	
	// TMap<FName, FPAShopTable> ShopTableData;
	// TMap<FName, FPAUIClassTable> UIClassTableData;
	TMap<FName, TObjectPtr<UDataTable>> Datas;
};

// 데이터 추가 시 작업
// template <typename T>
// const TMap<FName, T>& UPADataManager::GetData() const
// {
// 	if constexpr (TIsSame<T, FPAUIClassTable>::Value)
// 	{
// 		return UIClassTableData;
// 	}
// 	else if constexpr (TIsSame<T, FPAShopTable>::Value)
// 	{
// 		return ShopTableData;  
// 	}
// 	else
// 	{
// 		return TMap<FName,T>();
// 	}
// }

template <typename T>
bool UPADataManager::LoadData(FName BPTableName, TMap<FName, T>& OutTableData)
{
	CHECK_NULLPTR_RETURN(Datas.Find(BPTableName), false);
	const TMap<FName, uint8*>& RowMap = Datas[BPTableName]->GetRowMap();

	for (auto& Pair : RowMap)
	{
		T* RowData = reinterpret_cast<T*>(Pair.Value);
		if (RowData)
		{
			OutTableData.Emplace(Pair.Key, *RowData);
		}
	}
	return  true;
}

// template <typename T>
// void UPADataManager::LoadTable(UDataTable* DataTable, TMap<FName, T>& OutTableData)
// {
// 	CHECK_NULLPTR_RETURN(DataTable,);
// 	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
//
// 	for (auto& Pair : RowMap)
// 	{
// 		T* RowData = reinterpret_cast<T*>(Pair.Value);
// 		if (RowData)
// 		{
// 			OutTableData.Emplace(Pair.Key, *RowData);
// 		}
// 	}
// }
