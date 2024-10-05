// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectA/Data/Character/PACharacterControlData.h"

// Sets default values
APACharacterBase::APACharacterBase()
{
	// Find And Matching
	static ConstructorHelpers::FObjectFinder<UPACharacterControlData> QuaterDataRef
	(TEXT("/Script/ProjectA.PACharacterControlData'/Game/ProjectA/Data/Character/DA_Quater.DA_Quater'"));
	if(QuaterDataRef.Object)
	{
		CharacterControlData = QuaterDataRef.Object;
	}
}

void APACharacterBase::SetCharacterControlData(const class UPACharacterControlData* ControlData)
{
	ensure(CharacterControlData);
	
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}


