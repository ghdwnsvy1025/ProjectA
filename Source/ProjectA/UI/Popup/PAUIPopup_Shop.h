// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
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
	virtual void NativeConstruct() override;
	void Refresh();
	
	UFUNCTION()
	void OnButtonClickedFun();

	UFUNCTION(BlueprintCallable, Category =Hovering)
	void OnShowHoveringUI(const FName& ItemName, const FPAItemTable& ItemTable);
	
	UFUNCTION(BlueprintCallable, Category =Hovering)
	void OnHideHoveringUI(const class UPAItemButton* Button);
private:
	UFUNCTION()
	void OnVisibilityChangedFunc(ESlateVisibility CurVisibility);

protected:
	FOnVisibilityChangedEvent OnVisibilityChangedEvent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitBtn;

private:
	uint8 bIsInited : 1;
	uint8 bIsModify : 1;
};
