// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PACharacterBase.h"
#include "PACharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APACharacterPlayer : public APACharacterBase
{
	GENERATED_BODY()
public:
	APACharacterPlayer();

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
};
