// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAUIBase.h"


class UAbilitySystemComponent* UPAUIBase::GetAbilitySystemComponent() const
{
	return  ASC;
}

void UPAUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}
