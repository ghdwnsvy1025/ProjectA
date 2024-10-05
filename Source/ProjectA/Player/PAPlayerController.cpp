// Fill out your copyright notice in the Description page of Project Settings.


#include "PAPlayerController.h"

void APAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}
