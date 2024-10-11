// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PAPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTA_API APAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APAPlayerController();

	virtual void SetupInputComponent() override;
	void MouseMove(const FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MouseMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputMappingContext> MouseMoveContext;


};
