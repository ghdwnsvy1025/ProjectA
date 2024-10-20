// Fill out your copyright notice in the Description page of Project Settings.


#include "PAUIPopup_Hovering.h"

#include "ProjectA.h"
#include "Components/Button.h"
#include "Components/VerticalBoxSlot.h"
#include "Manager/PAInventoryManager.h"
#include "Manager/PAItemManager.h"

void UPAUIPopup_Hovering::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPAUIPopup_Hovering::Refresh(const FName& ObjectName, const FPAItemTable& ItemTable)
{
	UWorld* World = GetWorld();

	CHECK_NULLPTR_RETURN(World,);
	CHECK_NULLPTR_RETURN(VerticalBox,);
	CHECK_NULLPTR_RETURN(BgImg,);
	CHECK_NULLPTR_RETURN(ItemImg,);

	UPAInventoryManager* InventoryManager = World->GetGameInstance()->GetSubsystem<UPAInventoryManager>();
	UPAItemManager* ItemManager = World->GetSubsystem<UPAItemManager>();
	FName SpriteName = FName(*ItemTable.SpriteName);
	float FontSize = 35.f;

	// Item Img
	UTexture2D* Texture = ItemManager->GetTexture(SpriteName);
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture);
	Brush.ImageSize = FVector2D(256, 256);
	ItemImg->SetBrush(Brush);

	// Item Txt

	ItemTxt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *ObjectName.ToString())));
	ItemTxt->SetJustification(ETextJustify::Center);
	FSlateFontInfo ObjectFontInfo = ItemTxt->GetFont();
	ObjectFontInfo.Size = FontSize;
	ObjectFontInfo.TypefaceFontName = TEXT("Bold");
	ItemTxt->SetFont(ObjectFontInfo);

	VerticalBox->ClearChildren();
	AddText(TEXT("물리 데미지"), ItemTable.PhysicalDamage, 24);
	AddText(TEXT("마법 데미지"), ItemTable.MagicDamage, 24);
	AddText(TEXT("물리 방어력"), ItemTable.PhysicalDefense, 24);
	AddText(TEXT("마법 방어력"), ItemTable.MagicDefense, 24);
	AddText(TEXT("공격 속도"), ItemTable.AttackSpeed, 24);
	AddText(TEXT("크리티컬"), ItemTable.CriticalChance, 24);
}

void UPAUIPopup_Hovering::AddText(const FName& ValueName, float Value, float FontSize)
{
	const float epsilon = 1e-6f; 

	if (FMath::Abs(Value) < epsilon)
	{
		return;
	}

	UTextBlock* ValueText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	ValueText->SetText(FText::FromString(FString::Printf(TEXT("+%0.f %s"), Value, *ValueName.ToString())));
	ValueText->SetJustification(ETextJustify::Left);
	FSlateFontInfo FontInfo = ValueText->GetFont();
	FontInfo.Size = FontSize;
	ValueText->SetFont(FontInfo);

	UVerticalBoxSlot* VerticalSlot = VerticalBox->AddChildToVerticalBox(ValueText);
	if (VerticalSlot)
	{
		// VerticalSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		// VerticalSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		VerticalSlot->SetPadding(FMargin(FVector2d(50.0, 10.0)));
	}
}
