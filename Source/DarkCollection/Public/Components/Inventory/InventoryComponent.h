// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DarkCollectionTypes.h"
#include "Data/Structs/InventoryItemSlotData.h"
//#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

class AEquipableItem;
class AEquipableDocumentation;
struct FInventoryItemSlotData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FInventoryItemSlotData, ItemData);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKCOLLECTION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();



	////////////////////////////////////////////// DOCUMENTATION ////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Inventory | Documentation")
	TArray<UBaseDocumentationData*> GetDocumentationArray() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory | Documentation")
	void SetDocumentationArray(TArray<UBaseDocumentationData*> NewDocsArray);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Documentation")
	TArray<UBaseDocumentationData*> GetAllDocumentsOfType(EDocumentationType DocumentationType = EDocumentationType::None) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory | Documentation")
	void AddDocumentation(UBaseDocumentationData* Documentation);

	

	////////////////////////////////////////////// ITEMS ////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	TArray<FInventoryItemSlotData> GetItemsArray() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	void SetItemsArray(TArray<FInventoryItemSlotData> NewItemsArray);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	void AddItem(AEquipableItem* ItemToAdd, uint8 ItemsCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	void GiveItem(TSubclassOf<AEquipableItem> ItemToAdd, uint8 ItemsCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	uint8 RemoveItem(AEquipableItem* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Items")
	bool ContainsItem(FName ItemName);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

private: 

	UPROPERTY()
	TArray<UBaseDocumentationData*> DocumentationArray;

	UPROPERTY()
	TArray<FInventoryItemSlotData> ItemArray; 

};
