// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "PAItem.generated.h"

USTRUCT(BlueprintType)
struct FItemInformation 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInformation")
	int MaxCount;
};

UCLASS()
class PROJECTA_API APAItem : public AActor, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	APAItem();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
