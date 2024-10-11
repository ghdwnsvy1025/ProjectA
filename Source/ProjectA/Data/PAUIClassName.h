#pragma once
#include "Engine/DataTable.h"
#include "PAUIClassName.generated.h"

USTRUCT(BlueprintType)
struct FPAUIClassName : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPAUIClassName(){};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIClassName)
	FName ClassName;
};