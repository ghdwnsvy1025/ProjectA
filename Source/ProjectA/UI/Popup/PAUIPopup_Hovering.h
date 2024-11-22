// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Data/PAItemTable.h"
#include "UI/Popup/PAUIPopup.h"
#include "PAUIPopup_Hovering.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIPopup_Hovering : public UPAUIPopup
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void Refresh(const FName& ObjectName, const FPAItemTable& ItemTable);

private:
	void AddText(const FName& ValueName, float Value, float FontSize);
private:
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UImage> 	BgImg;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UImage> 	ItemImg;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UTextBlock> 	ItemTxt;
	
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;

	
};
