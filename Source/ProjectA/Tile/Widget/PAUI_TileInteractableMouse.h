// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/PAUIBase.h"
#include "PAUI_TileInteractableMouse.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonDelegate);
UCLASS()
class PROJECTA_API UPAUI_TileInteractableMouse : public UPAUIBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnButtonClickedFunc();

	UFUNCTION(BlueprintCallable)
	void OnButtonHoveredFunc();

	UFUNCTION(BlueprintCallable)
	void OnButtonUnHoveredFunc();

private:
	void SetOppacity(bool IsZero);
public:
	UPROPERTY(BlueprintAssignable)
	FButtonDelegate OnButtonDelgate;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TxtStep;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> TileButton;

	UPROPERTY(EditAnywhere, Category = TileTag)
	FGameplayTag TileTag;
private:
	FLinearColor OriginalColor;

	
};
