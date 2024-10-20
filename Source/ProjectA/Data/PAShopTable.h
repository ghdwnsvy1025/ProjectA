#pragma once

#include "PADataTable.h"
#include "PAShopTable.generated.h"



USTRUCT(BlueprintType)
struct FPAShopTable : public FPADataTable
{
	GENERATED_BODY()
	
	FPAShopTable(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int ItemIndex;
};
USTRUCT(BlueprintType)
struct FInnerShopTable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopManager")
	TMap<FName, FPAShopTable> InnerMap; 
};
