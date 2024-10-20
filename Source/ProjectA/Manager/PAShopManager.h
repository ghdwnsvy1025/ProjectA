// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectA.h"
#include "Data/PAShopTable.h"
#include "PAShopManager.generated.h"
/**
 * 
 */

UCLASS()
class PROJECTA_API UPAShopManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void Init(UWorld* World);
	void GetTable(FName TableName, TMap<FName, FPAShopTable>& Table) const
	{
		if (ShopTables.Find(TableName))
		{
			
			Table = ShopTables[TableName].InnerMap;
		}
	}

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UPROPERTY(EditAnywhere, Category = ShopManager)
	TMap<FName, FInnerShopTable> ShopTables;
};
