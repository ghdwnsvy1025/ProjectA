// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/PAUIBase.h"
#include "PAUIPopup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIPopup : public UPAUIBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

};
