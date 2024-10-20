// Fill out your copyright notice in the Description page of Project Settings.


#include "PAUIPopup_Shop.h"

#include "ProjectA.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Data/PAShopTable.h"
#include "Manager/PADataManager.h"
#include "Manager/PAShopManager.h"


void UPAUIPopup_Shop::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnVisibilityChangedEvent.AddDynamic(this,&UPAUIPopup_Shop::OnVisibilityChangedFunc);
	Refresh();
}

void UPAUIPopup_Shop::Refresh()
{
	UWorld* World = GetWorld();
	CHECK_NULLPTR_RETURN(World,);
	CHECK_NULLPTR_RETURN(VerticalBox,);
	CHECK_NULLPTR_RETURN(ScrollBox,);
	
	TMap<FName, FPAShopTable> ShopTable;
	World->GetSubsystem<UPAShopManager>()->LoadData(TagName, ShopTable);
	
	for(auto& Pair : ShopTable)
	{
		FName ObjectName = Pair.Key;
		FPAShopTable Table = Pair.Value;

		UButton* Button = NewObject<UButton>(this, UButton::StaticClass());
		UHorizontalBox* HorizontalBox = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());

		UTextBlock* QuantityText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		USpacer* QuantitySpacer = NewObject<USpacer>(this, USpacer::StaticClass());
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Table.Quantity)));

		UTextBlock* ObjectText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		USpacer* ObjectSpacer = NewObject<USpacer>(this, USpacer::StaticClass());
		ObjectText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *ObjectName.ToString())));

		UTextBlock* PriceText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		USpacer* PriceSpacer = NewObject<USpacer>(this, USpacer::StaticClass());
		PriceText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Table.Price)));
		
		HorizontalBox->AddChildToHorizontalBox(QuantityText);
		HorizontalBox->AddChildToHorizontalBox(QuantitySpacer);

		HorizontalBox->AddChildToHorizontalBox(ObjectText);
		HorizontalBox->AddChildToHorizontalBox(ObjectSpacer);

		HorizontalBox->AddChildToHorizontalBox(PriceText);
		HorizontalBox->AddChildToHorizontalBox(PriceSpacer);
		
		Button->AddChild(HorizontalBox);

		VerticalBox->AddChildToVerticalBox(Button);
	}
}

void UPAUIPopup_Shop::OnVisibilityChangedFunc(ESlateVisibility CurVisibility)
{
	if(CurVisibility == ESlateVisibility::Visible)
		Refresh();
}
