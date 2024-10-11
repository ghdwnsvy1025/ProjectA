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
	
}

void APAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(MouseMoveContext, 0);
	}
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseMoveAction, ETriggerEvent::Triggered, this,&APAPlayerController::MouseMove);
	
}


void APAPlayerController::MouseMove(const FInputActionValue& Value)
{
	FVector2d MouseMovement = Value.Get<FVector2d>();
}
