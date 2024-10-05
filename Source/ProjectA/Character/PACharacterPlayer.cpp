// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectA/Data/Character/PACharacterControlData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

APACharacterPlayer::APACharacterPlayer()
{
	// Camera

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Input
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef
	(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_QuaterMove.IA_QuaterMove'"));
	if(InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}
}

void APACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::QuaterMove);

}

void APACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterControlData(CharacterControlData);
}

void APACharacterPlayer::SetCharacterControlData(const class UPACharacterControlData* ControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	ensure(ControlData);
	
	// Camera
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

	// Input Context
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(ControlData->InputMappingContext, 0);
	}
}

void APACharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	// 마우스 클릭이 True일 때 처리
	if (Value.Get<bool>())
	{
		// 마우스 위치에서 레이캐스트 실행

		APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
		FHitResult Hit;

		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		
		if (Hit.bBlockingHit)
		{
			MoveToLocation(Hit.ImpactPoint);
		}
	}
}

void APACharacterPlayer::MoveToLocation(const FVector& Location)
{
	BeginLocation = GetActorLocation();
	TargetLocation = Location; // 목표 위치 설정
	MovementTime = 3.0f; // 이동 시간 설정
	ElapsedTime = 0.0f; // 경과 시간 초기화

	// 이동 시작
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &APACharacterPlayer::MoveCharacter, 0.01f, true);
	});
}

void APACharacterPlayer::MoveCharacter()
{
	// 경과 시간 업데이트
	ElapsedTime += 0.01f;

	// 이동 비율 계산
	float Alpha = FMath::Clamp(ElapsedTime / MovementTime, 0.0f, 1.0f);
    
	// 현재 위치에서 목표 위치로 보간
	FVector NewLocation = FMath::Lerp(BeginLocation, TargetLocation, Alpha);
	SetActorLocation(NewLocation);

	// 목표 위치에 도달하면 이동 정지
	if (Alpha >= 0.99f)
	{
		StopMovement();
	}
}

void APACharacterPlayer::StopMovement()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}
