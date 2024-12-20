// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlateWrapperTypes.h"
#include "PAUIManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIManager : public UObject
{
	GENERATED_BODY()

public:
	UPAUIManager();

	static UPAUIManager& Get();
	void Init(UWorld* World);
	void ShowPopup(const FName& Name, ESlateVisibility Visible = ESlateVisibility::Visible);
	void ShowScene(const FName& MapName);
	void ClosePopup();

	class UUserWidget* GetPopupUI(const FName& Name)
	{
		if (Popups.Find(Name))
		{
			return  Popups[Name];
		}
		else
		{
			return nullptr;
		}
	}

private:
	void CreateAndSaveUI(UWorld* World);
	void ExtractStringParts(const FString& InputString, FString& OutUIType, FString& OutName);

private:
	UPROPERTY(EditAnywhere, Category = UI)
	TMap<FName, TObjectPtr<class UUserWidget>> Popups;

	UPROPERTY(EditAnywhere, Category = UI)
	TMap<FName, TObjectPtr<class UUserWidget>> Scenes;

	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<class UUserWidget> Scene;

	UPROPERTY(EditAnywhere, Category = UI)
	TArray<TObjectPtr<class UUserWidget>> PopupStack;

private:
	int LayerOrder;
};
