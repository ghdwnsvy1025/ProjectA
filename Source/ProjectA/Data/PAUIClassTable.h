#pragma once
#include "PADataTable.h"
#include "Engine/DataTable.h"
#include "PAUIClassTable.generated.h"

USTRUCT(BlueprintType)
struct FPAUIClassTable : public FPADataTable
{
	GENERATED_BODY()
	
	FPAUIClassTable(){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIClassData)
	FName ClassName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIClassData)
	FName Tag;
};