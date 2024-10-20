// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "UI/Popup/PAUIPopup.h"
#include "PAUIPopup_Shop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIPopup_Shop : public UPAUIPopup
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	void Refresh();
private:
	UFUNCTION()
	void OnVisibilityChangedFunc(ESlateVisibility CurVisibility);
protected:
	FOnVisibilityChangedEvent OnVisibilityChangedEvent;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

};
