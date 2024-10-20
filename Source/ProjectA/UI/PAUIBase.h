// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PAUIBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTagName(const FName& Name){TagName = Name;}
protected:
	
	UPROPERTY()
	FName TagName;
// protected:
// 	virtual void NativeOnInitialized() override;
// 	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
// 	
// 	TObjectPtr<class UAbilitySystemComponent> ASC;
};
