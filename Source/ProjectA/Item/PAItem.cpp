// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PAItem.h"

APAItem::APAItem()
{

}

UAbilitySystemComponent* APAItem::GetAbilitySystemComponent() const
{
	return  ASC;
}

