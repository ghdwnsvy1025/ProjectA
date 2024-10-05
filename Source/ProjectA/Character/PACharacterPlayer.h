// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PACharacterBase.h"
#include "PACharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APACharacterPlayer : public APACharacterBase
{
	GENERATED_BODY()

public:
	APACharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
protected:
	virtual  void BeginPlay() override;
	
	// Character Control Data
	virtual void SetCharacterControlData(const class UPACharacterControlData* ControlData) override;

	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	void QuaterMove(const FInputActionValue& Value);
	void MoveToLocation(const FVector& Location);
	void MoveCharacter();
	void StopMovement();

	// Move
protected:
	FTimerHandle MoveTimerHandle;
	FVector BeginLocation;
	FVector TargetLocation; // 목표 위치
	float MovementTime; // 이동 시간
	float ElapsedTime; // 경과 시간
};
