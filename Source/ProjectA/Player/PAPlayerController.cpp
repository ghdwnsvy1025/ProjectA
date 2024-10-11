// Fill out your copyright notice in the Description page of Project Settings.


#include "PAPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectA.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetInteractionComponent.h"

APAPlayerController::APAPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	// FInputModeGameAndUI InputMode;
	// InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// SetInputMode(InputMode);
	
}

