// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAUIBase_InventorySubTypeSlot.h"

#include "PAItemButton.h"
#include "PAUIPopup_Hovering.h"
#include "ProjectA.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetInteractionComponent.h"
#include "Manager/PAInventoryManager.h"
#include "Manager/PAItemManager.h"
#include "Manager/PAUIManager.h"
#include "Tag/PAGameplayTag.h"

class UButtonSlot;
class UTextBlock;

void UPAUIBase_InventorySubTypeSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bIsInit = false;
	bIsModified = false;
	bIsHovering = false;
	ItemType = EItemType::Weapon;
	OnVisibilityChangedEvent.AddDynamic(this, &UPAUIBase_InventorySubTypeSlot::OnVisibilityChangedEventFunc);
}

void UPAUIBase_InventorySubTypeSlot::NativeConstruct()
{
	Super::NativeConstruct();
	// PA_LOG(LogTest, Log, TEXT("NativeConstruct %d"), ItemType);
	// if (bIsInit == true)
	Refresh();
}

void UPAUIBase_InventorySubTypeSlot::Init(EItemType Type)
{
	ItemType = Type;
	// Refresh();
	// PA_LOG(LogTest, Log, TEXT("Init %d"), ItemType);
	//
	// bIsInit = true;
}

void UPAUIBase_InventorySubTypeSlot::Refresh()
{
	UWorld* World = GetWorld();


	CHECK_NULLPTR_RETURN(World,);
	// CHECK_NULLPTR_RETURN(VerticalBox,);

	if (MyVertical == nullptr)
	{
		PA_LOG(LogTest, Warning, TEXT("VericalBox nullptr %d, %p"), ItemType, this);
		return;
	}

	UPAInventoryManager* InventoryManager = World->GetGameInstance()->GetSubsystem<UPAInventoryManager>();
	UPAItemManager* ItemManager = World->GetSubsystem<UPAItemManager>();

	CHECK_NULLPTR_RETURN(InventoryManager,);
	CHECK_NULLPTR_RETURN(ItemManager,);

	TMap<FName, FPAItemTable> ItemTable;
	if (!InventoryManager->GetTable(ItemType, ItemTable))
	{
		PA_LOG(LogTest, Warning, TEXT("Failed To Load ItemTable"));
		return;
	}

	for (auto& Pair : ItemTable)
	{
		FName ObjectName = Pair.Key;
		FPAItemTable Table = Pair.Value;
		FName SpriteName = FName(*Pair.Value.SpriteName);
		int Quantity = InventoryManager->GetItemQuantity(ObjectName);

		float FontSize = 24.f;
		// Button
		UPAItemButton* Button = NewObject<UPAItemButton>(this, UPAItemButton::StaticClass());

		// Horizon Box
		UHorizontalBox* HorizontalBox = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());

		// Image
		UImage* Image = NewObject<UImage>(this, UImage::StaticClass());
		UTexture2D* Texture = ItemManager->GetTexture(SpriteName);
		FSlateBrush Brush;
		Brush.SetResourceObject(Texture);
		Brush.ImageSize = FVector2D(50, 50);
		Image->SetBrush(Brush);

		// Text Object
		UTextBlock* ObjectText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		ObjectText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *ObjectName.ToString())));
		ObjectText->SetJustification(ETextJustify::Left);
		FSlateFontInfo ObjectFontInfo = ObjectText->GetFont();
		ObjectFontInfo.Size = FontSize;
		ObjectText->SetFont(ObjectFontInfo);

		UHorizontalBoxSlot* ObjectSlot = HorizontalBox->AddChildToHorizontalBox(ObjectText);
		ObjectSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		ObjectSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		// Text quantity
		UTextBlock* QuantityText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("[%d]"), Quantity)));
		QuantityText->SetJustification(ETextJustify::Left);
		FSlateFontInfo QuantityFontInfo = ObjectText->GetFont();
		QuantityFontInfo.Size = FontSize;
		QuantityText->SetFont(QuantityFontInfo);

		USpacer* Spacer = NewObject<USpacer>(this, USpacer::StaticClass());
		// Spacer->SetSize(FVector2D(40.f, 1.f));

		HorizontalBox->AddChild(Image);
		HorizontalBox->AddChild(ObjectText);
		HorizontalBox->AddChild(QuantityText);
		HorizontalBox->AddChild(Spacer);
		Button->AddChild(HorizontalBox);

		TArray<UPanelSlot*> ButtonSlots = Button->GetSlots();
		if (ButtonSlots.IsEmpty() == false)
		{
			UButtonSlot* ButtonSlot = Cast<UButtonSlot>(ButtonSlots[0]);
			if (ButtonSlot)
			{
				ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
				// ButtonSlot->SetPadding(FMargin(FVector2d(4.0,2.0)));
			}
		}

		UVerticalBoxSlot* VerticalSlot = MyVertical->AddChildToVerticalBox(Button);
		if (VerticalSlot)
		{
			VerticalSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			VerticalSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			VerticalSlot->SetPadding(FMargin(FVector2d(500.0, 500.0)));
		}
		Button->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
		Button->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::Box;
		Button->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::Box;

		MyVertical->AddChild(Button);
		USpacer* ButtonSpacer = NewObject<USpacer>(this, USpacer::StaticClass());
		ButtonSpacer->SetSize(FVector2D(1.f, 5.f));

		UVerticalBoxSlot* SpacerVerticalSlot = MyVertical->AddChildToVerticalBox(ButtonSpacer);
		if (SpacerVerticalSlot)
		{
			SpacerVerticalSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			SpacerVerticalSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			SpacerVerticalSlot->SetPadding(FMargin(FVector2d(5.0, 5.0)));
		}
		Button->SetValue(ObjectName, Table);
		Button->CustomOnHovered.AddDynamic(this, &UPAUIBase_InventorySubTypeSlot::ShowHoveringUI);
		Button->CustomOnUnHovered.AddDynamic(this, &UPAUIBase_InventorySubTypeSlot::HideHoveringUI);
	}
}

void UPAUIBase_InventorySubTypeSlot::OnVisibilityChangedEventFunc(ESlateVisibility SlateVisibility)
{
	// Refresh();
}

void UPAUIBase_InventorySubTypeSlot::ShowHoveringUI(const FName& ItemName, const FPAItemTable& ItemTable)
{
	PA_LOG(LogTest, Log, TEXT("Hovering"));

	UPAUIPopup_Hovering* HoveringUI = Cast<UPAUIPopup_Hovering>(
		UPAUIManager::Get().GetPopupUI(PATAG_UI_POPUP_HOVERING.GetTagName()));
	if (HoveringUI)
	{
		HoveringUI->Refresh(ItemName, ItemTable);
	}
	UPAUIManager::Get().ShowPopup(PATAG_UI_POPUP_HOVERING.GetTagName(), ESlateVisibility::HitTestInvisible);
}

void UPAUIBase_InventorySubTypeSlot::HideHoveringUI(const UPAItemButton* Button)
{
	// if(!IsHovered())
	// {
	UPAUIManager::Get().ClosePopup();
	PA_LOG(LogTest, Log, TEXT("Close Hovering"));
	// }
}
