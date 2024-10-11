// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PACameraPawn.generated.h"

UCLASS()
class PROJECTA_API APACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APACameraPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	void OnMouseClikedFunc(const FInputActionValue& Value);
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void MouseDrag(const FInputActionValue& Value);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MouseDragAction;

	// Input Setction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputMappingContext> MouseClickContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MouseClickAction;


	// Widget
	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteractionComponent;

	UPROPERTY(EditAnywhere)
	float CameraMoveSpeed;
	
	UPROPERTY(EditAnywhere)
	float ZoomSpeed;

	UPROPERTY(EditAnywhere)
	float MinTargetArmLength;

	UPROPERTY(EditAnywhere)
	float MaxTargetArmLength;

	UPROPERTY(EditAnywhere)
	float TraceDistance;
};
