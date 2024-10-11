// Fill out your copyright notice in the Description page of Project Settings.


#include "PATile.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "ProjectA.h"
#include "Components/WidgetInteractionComponent.h"
#include "Manager/PAUIManager.h"
#include "Widget/PATile_WidgetComponent.h"

APATile::APATile()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = StaticMesh;
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	// StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshRef
	(TEXT(
		"/Script/Engine.StaticMesh'/Game/Asset/Map/Viliage/HexTile_Clay_HexTop_ClayGround.HexTile_Clay_HexTop_ClayGround'"));
	if (TileMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(TileMeshRef.Object);
	}

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	HoveringUI = CreateDefaultSubobject<UPATile_WidgetComponent>(TEXT("HoveringUI"));
	HoveringUI->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> HoveringTileRef
		(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_TileInteractableMouse.WBP_TileInteractableMouse_C'"));

	if (HoveringTileRef.Class)
	{
		HoveringUI->SetWidgetClass(HoveringTileRef.Class);
		HoveringUI->SetWidgetSpace(EWidgetSpace::World);
	}


}

void APATile::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	PA_LOG(LogTest, Log, TEXT("Hovered"));

	HoveringUI->ShowWidget();
}

void APATile::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	PA_LOG(LogTest, Log, TEXT("Over Hover"));
	HoveringUI->HiddenWidget();
}


void APATile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ASC->InitAbilityActorInfo(this, this);

	// FGameplayAbilitySpec Spec(TargetAblitiyClass);
	// ASC->GiveAbility(Spec);
}

class UAbilitySystemComponent* APATile::GetAbilitySystemComponent() const
{
	return ASC;
}
