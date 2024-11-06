// Fill out your copyright notice in the Description page of Project Settings.


#include "PAUIPopup_Shop.h"

#include "PAUIPopup_Hovering.h"
#include "ProjectA.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/PAShopTable.h"
#include "Manager/PAShopManager.h"
#include "Manager/PAUIManager.h"
#include "Tag/PAGameplayTag.h"
#include "UI/PAItemButton.h"


void UPAUIPopup_Shop::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	bIsInited = false;
	bIsModify = false;
	OnVisibilityChangedEvent.AddDynamic(this, &UPAUIPopup_Shop::OnVisibilityChangedFunc);
	ExitBtn->OnReleased.AddDynamic(this, &UPAUIPopup_Shop::OnButtonClickedFun);
}

void UPAUIPopup_Shop::NativeConstruct()
{
	Super::NativeConstruct();

	Refresh();
}

void UPAUIPopup_Shop::Refresh()
{
	if (bIsInited && !bIsModify)
		return;

	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);
	CHECK_NULLPTR_RETURN(VerticalBox,);
	CHECK_NULLPTR_RETURN(ScrollBox,);

	TMap<FName, FPAShopTable> ShopTable;
	World->GetSubsystem<UPAShopManager>()->GetTable(TagName, ShopTable);

	for (auto& Pair : ShopTable)
	{
		FName ObjectName = Pair.Key;
		FPAShopTable Table = Pair.Value;
		float FontSize = 20.f;
		// Button
		UPAItemButton* Button = NewObject<UPAItemButton>(this, UPAItemButton::StaticClass());
		
		// Button->Init(ObjectName, Table);
		// Horizon Box
		UHorizontalBox* HorizontalBox = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());

		//Text Quantity
		UButton* QuantityButton = NewObject<UButton>(this, UButton::StaticClass());

		UTextBlock* QuantityText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Table.Quantity)));
		QuantityText->SetJustification(ETextJustify::Left);
		FSlateFontInfo FontInfo = QuantityText->GetFont();
		FontInfo.Size = FontSize;
		QuantityText->SetFont(FontInfo);

		UHorizontalBoxSlot* QuantitySlot = HorizontalBox->AddChildToHorizontalBox(QuantityText);
		QuantitySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
		QuantitySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		QuantityButton->AddChild(QuantityText);
		QuantityButton->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		QuantityButton->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
		QuantityButton->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;

		// Text Object
		UButton* ObjectButton = NewObject<UButton>(this, UButton::StaticClass());
		UTextBlock* ObjectText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		ObjectText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *ObjectName.ToString())));
		ObjectText->SetJustification(ETextJustify::Left);
		FSlateFontInfo ObjectFontInfo = ObjectText->GetFont();
		ObjectFontInfo.Size = FontSize;
		ObjectText->SetFont(ObjectFontInfo);

		UHorizontalBoxSlot* ObjectSlot = HorizontalBox->AddChildToHorizontalBox(ObjectText);
		ObjectSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
		ObjectSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		ObjectButton->AddChild(ObjectText);
		ObjectButton->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		ObjectButton->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
		ObjectButton->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;

		// Text Price
		UButton* PriceButton = NewObject<UButton>(this, UButton::StaticClass());

		UTextBlock* PriceText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		PriceText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Table.Price)));
		PriceText->SetJustification(ETextJustify::Left);
		FSlateFontInfo PriceFontInfo = ObjectText->GetFont();
		PriceFontInfo.Size = FontSize;
		PriceText->SetFont(PriceFontInfo);

		UHorizontalBoxSlot* PriceSlot = HorizontalBox->AddChildToHorizontalBox(PriceText);
		PriceSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
		PriceSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		PriceButton->AddChild(PriceText);
		PriceButton->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		PriceButton->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
		PriceButton->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;

		UHorizontalBoxSlot* HorizontalBoxQuantitySlot = HorizontalBox->AddChildToHorizontalBox(QuantityButton);
		if (HorizontalBoxQuantitySlot)
		{
			HorizontalBoxQuantitySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
			HorizontalBoxQuantitySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			FSlateChildSize QuantityButtonSize(ESlateSizeRule::Fill);
			QuantityButtonSize.Value = 0.1f;
			HorizontalBoxQuantitySlot->SetSize(QuantityButtonSize);
		}

		UHorizontalBoxSlot* HorizontalBoxObjectSlot = HorizontalBox->AddChildToHorizontalBox(ObjectButton);
		if (HorizontalBoxObjectSlot)
		{
			HorizontalBoxObjectSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
			HorizontalBoxObjectSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			FSlateChildSize ObjectButtonSize(ESlateSizeRule::Fill);
			ObjectButtonSize.Value = 0.5f;
			HorizontalBoxObjectSlot->SetSize(ObjectButtonSize);
		}
		UHorizontalBoxSlot* HorizontalBoxPriceSlot = HorizontalBox->AddChildToHorizontalBox(PriceButton);
		if (HorizontalBoxPriceSlot)
		{
			HorizontalBoxPriceSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
			HorizontalBoxPriceSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			FSlateChildSize PriceButtonSize(ESlateSizeRule::Fill);
			PriceButtonSize.Value = 0.1f;
			HorizontalBoxPriceSlot->SetSize(PriceButtonSize);
		}

		Button->AddChild(HorizontalBox);
		TArray<UPanelSlot*> ButtonSlots = Button->GetSlots();
		if (ButtonSlots.IsEmpty() == false)
		{
			UButtonSlot* ButtonSlot = Cast<UButtonSlot>(ButtonSlots[0]);
			if (ButtonSlot)
			{
				ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}
		}

		UVerticalBoxSlot* VerticalSlot = VerticalBox->AddChildToVerticalBox(Button);
		if (VerticalSlot)
		{
			VerticalSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			VerticalSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
		// Button->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		// Button->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
		// Button->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;

		TArray<UPanelSlot*> ScrollSlots = ScrollBox->GetSlots();
		if (ScrollSlots.IsEmpty() == false)
		{
			UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ScrollSlots[0]);
			if (ScrollSlot)
			{
				ScrollSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				ScrollSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}
		}
	}

	bIsInited = true;
}


void UPAUIPopup_Shop::OnVisibilityChangedFunc(ESlateVisibility CurVisibility)
{
	if (CurVisibility == ESlateVisibility::Visible)
		Refresh();
}

void UPAUIPopup_Shop::OnButtonClickedFun()
{
	UPAUIManager::Get().ClosePopup();
}

void UPAUIPopup_Shop::OnShowHoveringUI(const FName& ItemName, const FPAItemTable& ItemTable)
{
	UPAUIPopup_Hovering* HoveringUI = Cast<UPAUIPopup_Hovering>(
		UPAUIManager::Get().GetPopupUI(PATAG_UI_POPUP_HOVERING.GetTagName()));
	if (HoveringUI)
	{
		HoveringUI->Refresh(ItemName, ItemTable);
	}
	UPAUIManager::Get().ShowPopup(PATAG_UI_POPUP_HOVERING.GetTagName(), ESlateVisibility::HitTestInvisible);
}

void UPAUIPopup_Shop::OnHideHoveringUI(const class UPAItemButton* Button)
{
	UPAUIManager::Get().ClosePopup();
}
