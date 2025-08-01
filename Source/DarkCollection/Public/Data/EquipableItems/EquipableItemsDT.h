// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EquipableItemsDT.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKCOLLECTION_API FEquipableItemsDT : public FTableRowBase
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemID; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 ItemMaxCount; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<class AEquipableItem> ItemClass; 

};
