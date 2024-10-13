// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "PATile.generated.h"


UCLASS()
class PROJECTA_API APATile : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	APATile();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
	void ShowPopupUI();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayAbility> TargetAblitiyClass;

	UPROPERTY(EditAnywhere)
	FGameplayTag TileTag;

	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<class UPATile_WidgetComponent> HoveringUI;

};
