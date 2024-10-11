// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PATile_WidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPATile_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void InitWidget() override;
	void ShowWidget();
	void HiddenWidget();
};
