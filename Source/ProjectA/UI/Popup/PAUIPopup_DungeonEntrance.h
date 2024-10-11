// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Popup/PAUIPopup.h"
#include "PAUIPopup_DungeonEntrance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIPopup_DungeonEntrance : public UPAUIPopup
{
	GENERATED_BODY()

protected:
	void OnVisibilityChangedEvent(ESlateVisibility SlateVisibility);


};
