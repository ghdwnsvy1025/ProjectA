// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectA.h"
#include "Data/PAShopTable.h"

#include "PAShopManager.generated.h"
/**
 * 
 */

struct FPAItemTable;

UCLASS()
class PROJECTA_API UPAShopManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void Init(UWorld* World);
	void GetTable(FName TableName, TMap<int32, FPAShopTable>& Table) const
	{
		if (ShopTables.Find(TableName))
		{
			
			Table = ShopTables[TableName].InnerMap;
		}
	}
	void BuyItem(const FName& ShopName, const FPAItemTable& ItemTable);
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UPROPERTY(EditAnywhere, Category = ShopManager)
	TMap<FName, FInnerShopTable> ShopTables; // (상점 이름, 데이터)
};
