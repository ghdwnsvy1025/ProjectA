#pragma once

#include "PADataTable.h"
#include "PAShopTable.generated.h"



USTRUCT(BlueprintType)
struct FPAShopTable : public FPADataTable
{
	GENERATED_BODY()
	
	FPAShopTable(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShopData)
	int32 ItemIndex;
};
USTRUCT(BlueprintType)
struct FInnerShopTable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopInnerTable")
	TMap<int32, FPAShopTable> InnerMap; 
};
