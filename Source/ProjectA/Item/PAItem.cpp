// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PAItem.h"

#include "ProjectA.h"

APAItem::APAItem()
{
	PA_LOG(LogTest, Log, TEXT("Text"));
}

UAbilitySystemComponent* APAItem::GetAbilitySystemComponent() const
{
	return  ASC;
}

