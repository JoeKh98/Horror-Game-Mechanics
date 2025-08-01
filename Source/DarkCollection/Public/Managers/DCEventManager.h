// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DCEventManager.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UDCEventManager : public UObject
{
	GENERATED_BODY()

public: 
	// Getting manager's instance 
	static UDCEventManager* GetInstance(UWorld* World);

	// Register event
	void RegisterEvent(const FString& EventID, TFunction<void()> Callback); 

	// Call event
	void TriggerEvent(const FString& EventID); 

private: 
	// Stores all registrated events
	TMap<FString, TArray<TFunction<void()>>> Events; 
	
};
