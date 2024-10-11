// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/WidgetInteractionComponent.h"

APACharacterPlayer::APACharacterPlayer()
{
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;
	
	
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(FollowCamera);

	if(WidgetInteractionComponent)
	{
		WidgetInteractionComponent->InteractionDistance = 2000.f;
		WidgetInteractionComponent->bShowDebug = true;
		WidgetInteractionComponent->bEnableHitTesting= true;
		WidgetInteractionComponent->DebugColor=FColor::Green;
	}
}
