// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PACameraPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectA.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"

APACameraPawn::APACameraPawn()
{
	CameraMoveSpeed = 1000.f;
	ZoomSpeed = 500.f;
	MinTargetArmLength = 200.f;
	MaxTargetArmLength = 1000.f;
	TraceDistance= 5000.f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// WidgetInteractionComponent = CreateDefaultSubobject<
	// 	UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	// WidgetInteractionComponent->SetupAttachment(RootComponent);
	//
	// if (WidgetInteractionComponent)
	// {
	// 	WidgetInteractionComponent->InteractionDistance = 2000.f;
	// 	WidgetInteractionComponent->bShowDebug = true;
	// 	WidgetInteractionComponent->bEnableHitTesting = true;
	// 	WidgetInteractionComponent->DebugColor = FColor::Green;
	// }
}


void APACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (Controller)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MouseClickContext, 0);
		}
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

		// EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Triggered, this,
		//                                    &APACameraPawn::OnMouseClikedFunc);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this,
		                                   &APACameraPawn::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this,
		                                   &APACameraPawn::MoveRight);
		EnhancedInputComponent->BindAction(MouseDragAction, ETriggerEvent::Triggered, this,
		                                   &APACameraPawn::MouseDrag);
	}
}


void APACameraPawn::OnMouseClikedFunc(const FInputActionValue& Value)
{
	FVector2D MousePosition;

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController == nullptr)
		return;

	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	
	// 마우스 위치를 월드 좌표로 변환
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	// 마우스 위치에서 Line Trace 수행
	FHitResult HitResult;
	FVector Start = WorldLocation;
	FVector End = WorldLocation + (WorldDirection * TraceDistance); // Trace 길이 설정

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		WidgetInteractionComponent->SetCustomHitResult(HitResult);
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
		// PA_LOG(LogTest,Log,TEXT("%s"), *HitResult.GetActor()->GetName()); 
	}
}

void APACameraPawn::MoveForward(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	FVector Forward = GetActorForwardVector();
	AddActorWorldOffset(Forward * MovementVector.X * CameraMoveSpeed * GetWorld()->GetDeltaSeconds());
}

void APACameraPawn::MoveRight(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	FVector Right = GetActorRightVector();
	AddActorWorldOffset(Right * MovementVector.X * CameraMoveSpeed * GetWorld()->GetDeltaSeconds());
}

void APACameraPawn::MouseDrag(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - (MovementVector.X * ZoomSpeed),
	                                           MinTargetArmLength, MaxTargetArmLength);
}
