// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PAUIBase.h"
#include "PAUI_TileInteractableMouse.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUI_TileInteractableMouse : public UPAUIBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnVisibilityChangedFunc(ESlateVisibility SlateVisibility);

	UFUNCTION(BlueprintCallable)
	void OnButtonClickedFunc();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TxtStep;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> TileButton;
};
