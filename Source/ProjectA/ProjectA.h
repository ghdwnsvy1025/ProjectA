// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define PA_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("%s %s"), LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogTest, Log, All);

#define CHECK_NULLPTR_RETURN(Pointer, ReturnValue)                \
	if (!(Pointer))													   \
	{																	 \
		UE_LOG(LogTemp, Warning, TEXT("Null pointer: %s"), TEXT(#Pointer)); \
		return ReturnValue;													 \
	}