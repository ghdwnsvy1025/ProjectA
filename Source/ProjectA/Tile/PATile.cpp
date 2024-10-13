// Fill out your copyright notice in the Description page of Project Settings.


#include "PATile.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "ProjectA.h"
#include "Components/WidgetInteractionComponent.h"
#include "Manager/PAUIManager.h"
#include "Widget/PATile_WidgetComponent.h"
#include "Widget/PAUI_TileInteractableMouse.h"
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

void APATile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ASC->InitAbilityActorInfo(this, this);

	// FGameplayAbilitySpec Spec(TargetAblitiyClass);
	// ASC->GiveAbility(Spec);

}

void APATile::BeginPlay()
{
	Super::BeginPlay();

	// Temp -> 시점을 게임 시작 후에 해줘야함. 그전에 위젯이 안생길 수도 있음
	// 나중에 델리게이트 말고 그냥 외부에서 ShowPopupUI함수를 호출해서 팝업을 띄울 것임 
	UUserWidget* Test = HoveringUI->GetWidget();
	if(Test)
	{
		UPAUI_TileInteractableMouse* TileWidget = CastChecked<UPAUI_TileInteractableMouse>(Test);
		if(TileWidget)
		{
			TileWidget->OnButtonDelgate.AddDynamic(this, &APATile::ShowPopupUI);
		}
	}
	

}

void APATile::ShowPopupUI()
{
	UPAUIManager::Get().ShowPopup(TileTag.GetTagName());
}

class UAbilitySystemComponent* APATile::GetAbilitySystemComponent() const
{
	return ASC;
}
