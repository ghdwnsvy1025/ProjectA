#pragma once
#include "PADataTable.h"
#include "PAItemTable.generated.h"

UENUM()
enum class EItemType : uint8
{
	All,
	Weapon,
	Armor,
	Portion,
	Scroll,
};

UENUM()
enum class EEquipmentType :uint8
{
	Helm,
	Shouler,
	Chest,
	Gloves,
	Pants,
	Boots,
	Bow,
	Sword,
	Axe,
	Mace,
	Shield,
	Staff,
};
USTRUCT(BlueprintType)
struct FPAItemTable : public FPADataTable
{
	GENERATED_BODY()
	
	FPAItemTable(){};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float PhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float MagicDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float PhysicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float MagicDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	float CriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	FString SpriteName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	EEquipmentType EquipmentType;
	

	// Image
};
USTRUCT(BlueprintType)
struct FInnerItemTable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInnerStruct")
	TMap<int32, FPAItemTable> InnerMap; 
};
