// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractableObject.h"
#include "Engine/DataTable.h"
#include "EquipableItem.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API AEquipableItem : public AInteractableObject
{
	GENERATED_BODY()

public:

	AEquipableItem(); 


	virtual void Interact(ADCBaseCharacter* Character) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Consume(); 

	virtual void Consume_Implementation(); 

protected: 

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	//class UEquipableItemData* ItemData; 

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	//bool IsVisibleInInventory; 

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Settings")
	//bool IsConsumable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Settings")
	uint8 NumberOfItemsToAddInventory = 1; 
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true"))
	class ADCBaseCharacter* ItemOwner; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Settings", meta=(RowType="EquipableItemsDT"))
	FDataTableRowHandle ItemData; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Settings")
	bool bIsConsumable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Settings")
	bool bIsVisibleInInventory = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

public: 

	UFUNCTION(BlueprintCallable, Category = "Inventory Settings")
	uint8 GetStackMaxCount() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory Settings")
	FName GetItemName() const;

	UFUNCTION(BlueprintCallable, Category = "Item Settings")
	bool GetIsConsumable() const;

	UFUNCTION(BlueprintCallable, Category = "Item Settings")
	bool GetIsVisibleInInventory() const;

	UFUNCTION(BlueprintCallable, Category = "Item Settings")
	FString GetItemID() const; 


private:

	FString ItemID; 


};
