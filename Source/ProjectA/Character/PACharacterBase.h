// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacterBase.generated.h"

UCLASS()
class PROJECTA_API APACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APACharacterBase();

protected:
	virtual void SetCharacterControlData(const class UPACharacterControlData* ControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPACharacterControlData> CharacterControlData;
};
