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
	// StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
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
	// PA_LOG(LogTest, Log, TEXT("Hovered"));
	//
	// if(HoveringUI->GetWidget()->IsVisible() == false)
	// 	HoveringUI->ShowWidget();
}
// 객체 Begin -> 위젯 켜짐 -> 객체 End But Trace True
// -> 위젯 UnHover -> 델리게이트 실행 -> 객체 Begin
// But Trace in -> 위젯 끄지 않음 -> 객체 End -> 위젯 끔.
// Trace out -> 위젯 끔



void APATile::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	// PA_LOG(LogTest, Log, TEXT("Over Hover"));
	// if(HoveringUI->GetWidget()->IsVisible() == true)
	// 	HoveringUI->HiddenWidget();
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
