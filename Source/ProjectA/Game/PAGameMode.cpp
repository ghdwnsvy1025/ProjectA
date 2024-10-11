// Fill out your copyright notice in the Description page of Project Settings.


#include "PAGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Manager/PAUIManager.h"

void APAGameMode::BeginPlay()
{
	Super::BeginPlay();


}

void APAGameMode::StartPlay()
{
	Super::StartPlay();
	
	UPAUIManager::Get().Init(GetWorld());
	
	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	FString PreName = TEXT("UPAUIScene_");
	LevelName = PreName + LevelName;
	
	// UPAUIManager::Get().ShowScene(GetData(LevelName));
}
