#pragma once
#include "Engine/DataTable.h"
#include "PADataTable.generated.h"

USTRUCT(BlueprintType)
struct FPADataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	FPADataTable(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName TableName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int DataIndex;
};