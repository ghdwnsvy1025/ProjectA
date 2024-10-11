// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Scene/PAUIScene.h"
#include "PAUIScene_ViliageMap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIScene_ViliageMap : public UPAUIScene
{
	GENERATED_BODY()

protected:
	void OnVisibilityChangedEvent(ESlateVisibility SlateVisibility);
};
