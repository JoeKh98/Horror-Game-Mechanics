// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DarkCollectionHUD.generated.h"


class UUserWidget;

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API ADarkCollectionHUD : public AHUD
{
	GENERATED_BODY()

public: 

	void SetReticleMode(bool bIsInteracting);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ReticleWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PersonalRecordsMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

protected:

	virtual void BeginPlay() override; 



private:

	UPROPERTY()
	class UReticleWidget* ReticleWidget;
};
