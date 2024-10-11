// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "PAUIBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIBase : public UUserWidget, public  IAbilitySystemInterface
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
