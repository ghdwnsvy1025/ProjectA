#pragma once
#include "PADataTable.h"
#include "Engine/DataTable.h"
#include "PAShopTable.generated.h"

USTRUCT(BlueprintType)
struct FPAShopTable : public FPADataTable
{
	GENERATED_BODY()
	
	FPAShopTable(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SHOPDATA)
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SHOPDATA)
	int Price;
};