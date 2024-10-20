// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/PAUIManager.h"

#include "PADataManager.h"
#include "ProjectA.h"

#include "Blueprint/UserWidget.h"
#include "Data/PAUIClassTable.h"
#include "UI/Popup/PAUIPopup.h"

UPAUIManager::UPAUIManager()
{
	LayerOrder = 10;
}

UPAUIManager& UPAUIManager::Get()
{
	UPAUIManager* UIManger = CastChecked<UPAUIManager>(GEngine->GameSingleton);
	if (UIManger)
	{
		return *UIManger;
	}

#if WITH_EDITOR
	PA_LOG(LogTest, Error, TEXT("Invalid UIManger Singleton!"));
#endif

	return *NewObject<UPAUIManager>();
}

void UPAUIManager::Init(UWorld* World)
{
	CreateAndSaveUI(World);
}

void UPAUIManager::ShowPopup(const FName& Name, ESlateVisibility Visible)
{
	if (Popups.Find(Name) == false)
	{
		PA_LOG(LogTest, Error, TEXT("No %s UI"), *Name.ToString());
		return;
	}
	UUserWidget* Widget = Popups[Name];
	ensure(Widget);

	++LayerOrder;
	PopupStack.Emplace(Widget);
	if (Widget->IsInViewport() == false)
	{
		Widget->AddToViewport(LayerOrder);
	}
	else
	{
		Widget->SetVisibility(Visible);
	}
}

void UPAUIManager::ShowScene(const FName& MapName)
{
	if (Scenes.Find(MapName) == false)
	{
		PA_LOG(LogTest, Error, TEXT("Failed To %s SceneUI"), *MapName.ToString());
		return;
	}
	UUserWidget* Widget = Scenes[MapName];

	Scene = Widget;
	if (Scene->IsInViewport() == false)
	{
		Scene->AddToViewport(LayerOrder);
	}
	else
	{
		Scene->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPAUIManager::ClosePopup()
{
	if (PopupStack.IsEmpty() == false)
	{
		TObjectPtr<UUserWidget> Widget = PopupStack.Pop();
		CHECK_NULLPTR_RETURN(Widget,);

		if (Widget->IsVisible() == true)
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
			--LayerOrder;
		}
	}
}

void UPAUIManager::CreateAndSaveUI(UWorld* World)
{
	CHECK_NULLPTR_RETURN(World,);
	TMap<FName, FPAUIClassTable> Datas;

	if (World->GetSubsystem<UPADataManager>()->LoadData<FPAUIClassTable>(TEXT("PAUIClassNameTable"), Datas))
	{
		PA_LOG(LogTest, Warning, TEXT("Failed To LoadData"));
	}

	for (auto& Pair : Datas)
	{
		// Create Widget

		FPAUIClassTable* Table = &Pair.Value;
		if (Table->Tag.IsNone())
		{
			continue;
		}
		FString UIType;
		FString UIName;

		ExtractStringParts(Table->ClassName.ToString(), UIType, UIName);
		UClass* WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr,
		                                      *FString::Printf(
			                                      TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_%s.WBP_%s_C'"),
			                                      *UIName, *UIName));

		if (WidgetClass == nullptr)
		{
			PA_LOG(LogTest, Warning, TEXT("Failed To Read %s Widget Bluprint!"), *UIName);
			continue;
		}

		if (World)
		{
			UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);

			if (Widget == nullptr)
			{
				PA_LOG(LogTest, Error, TEXT("Failed To Read %s Widget"), *UIName);
				return;
			}

			// Save Widget
			if (UIType == TEXT("UIPopup"))
			{
				UPAUIPopup* Popup = Cast<UPAUIPopup>(Widget);
				if (Popup)
				{
					Popup->SetTagName(Table->Tag);
				}
				else
				{
					PA_LOG(LogTest, Warning, TEXT("Failed To Cast %s"), *UIName);
				}

				Popups.Emplace(Table->Tag, Popup);
			}
			else if (UIType == TEXT("UIScene"))
			{
				Scenes.Emplace(Table->Tag, Widget);
			}

			PA_LOG(LogTest, Log, TEXT("Success To Read %s UI!"), *UIName);
		}
	}
	PA_LOG(LogTest, Log, TEXT("UIManger Load Complete!"));
}

void UPAUIManager::ExtractStringParts(const FString& InputString, FString& OutUIType, FString& OutName)
{
	// "UPA 제거"
	FString CleanedString = InputString.Replace(TEXT("UPA"), TEXT(""));

	// "_" 기준으로 분리
	CleanedString.Split(TEXT("_"), &OutUIType, &OutName);
}
