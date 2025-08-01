// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemSlotData.generated.h"

/**
 * 
 */

class AEquipableItem; 

USTRUCT(BlueprintType)
struct DARKCOLLECTION_API FInventoryItemSlotData
{
	GENERATED_BODY()

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings", meta = (RowType = "EquipableItemsDT"))
	//FDataTableRowHandle ItemData;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot Data")
	//AEquipableItem* EquipedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	FName ItemName = FName("None");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot Data")
	uint8 CurrentCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	TSubclassOf<AEquipableItem> ItemClass; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	bool bIsVisibleInInventory; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	bool bIsConsumable; 

};
