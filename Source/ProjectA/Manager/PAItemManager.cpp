// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/PAItemManager.h"

#include "PADataManager.h"
#include "ProjectA.h"
#include "Data/PAItemTable.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UPAItemManager::Init(UWorld* World)
{
	CHECK_NULLPTR_RETURN(World,);

	FName WeaponTableName = TEXT("PAWeaponItemTable");
	LoadItem(EItemType::Weapon, WeaponTableName);
	
	FName ArmorTableName = TEXT("PAArmorItemTable");
	LoadItem(EItemType::Armor, ArmorTableName);

	PA_LOG(LogTest,Log,TEXT("ItemManger Load Complete!"));
}

void UPAItemManager::LoadItem(EItemType ItemType, FName& BPTableName)
{
	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);
	
	TMap<FName,FPAItemTable> ItemTable;
	if(!World->GetSubsystem<UPADataManager>()->LoadData(BPTableName,ItemTable))
	{
		PA_LOG(LogTest,Warning,TEXT("Failed To Load %sTable"),*BPTableName.ToString());
		return;
	}

	FInnerItemTable InnerTable;
	InnerTable.InnerMap = ItemTable;
	
	// FString LevelName = World->GetMapName();
	// LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	ItemTables.Emplace(ItemType,  InnerTable);

	LoadTexture(ItemType, ItemTable);
}

void UPAItemManager::LoadTexture(EItemType ItemType, const TMap<FName,FPAItemTable>& ItemTable)
{
	FString ParentPath = TEXT("/Script/Engine.Texture2D'/Game/Asset/UI/Icon/Base_RPG/");
	switch (ItemType)
	{
	case EItemType::Weapon:
		ParentPath += TEXT("Weapon/");
		break;
	case EItemType::Armor:
		ParentPath += TEXT("Armor/");
		break;
	default:
			break;
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	for(auto& Pair : ItemTable)
	{
		FString SpriteName = Pair.Value.SpriteName;
		FString Path =ParentPath + FString::Printf( TEXT("%s.%s' ") , *SpriteName, *SpriteName);
		FSoftObjectPath TextureRef(*Path);
		UTexture2D* LoadedTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Path)));

		if (!LoadedTexture)
		{
			PA_LOG(LogTest, Warning, TEXT("Failed to load texture at path: %s"), *Path);
		}
		else
		{
			Textures.Emplace(FName(*SpriteName), LoadedTexture);
			PA_LOG(LogTest, Log, TEXT("Successfully loaded texture: %s"), *SpriteName);
		}
	}
}
