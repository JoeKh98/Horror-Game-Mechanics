// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DCFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UDCFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Save")
	static FString GetImgDate(); 

	UFUNCTION(BlueprintPure, Category = "Save")
	static FString GetDate(); 

	UFUNCTION(BlueprintPure, Category = "Sounds")
	static UAudioComponent* Play2DSound(UObject* WorldContextObject, USoundBase* Sound, bool bIsStopExisting = false);
	
};
