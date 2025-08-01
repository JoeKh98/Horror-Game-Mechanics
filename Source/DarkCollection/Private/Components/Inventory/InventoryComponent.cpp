// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/InventoryComponent.h"
#include "Actors/Interactive/Equipable/EquipableItem.h"
#include "Data/Documentations/BaseDocumentationData.h"
#include "Data/Structs/InventoryItemSlotData.h"
//#include "Data/EquipableItems/EquipableItemsDT.h"
#include "Engine/DataTable.h"
#include "Actors/Interactive/Equipable/EquipableDocumentation.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::AddDocumentation(UBaseDocumentationData* Documentation)
{
	DocumentationArray.AddUnique(Documentation); 
}

TArray<FInventoryItemSlotData> UInventoryComponent::GetItemsArray() const
{
	return ItemArray;
}

void UInventoryComponent::SetItemsArray(TArray<FInventoryItemSlotData> NewItemsArray)
{
	ItemArray = NewItemsArray; 
}

void UInventoryComponent::AddItem(AEquipableItem* ItemToAdd, uint8 ItemsCount)
{
	uint8 ItemStackMaxCount = ItemToAdd->GetStackMaxCount(); 
	FInventoryItemSlotData NewItem;
	//NewItem.EquipedItem = ItemToAdd;
	NewItem.ItemName = ItemToAdd->GetItemName(); 
	NewItem.CurrentCount = FMath::Clamp(ItemsCount, 0, ItemStackMaxCount);
	NewItem.ItemClass = ItemToAdd->GetClass(); 
	NewItem.bIsVisibleInInventory = ItemToAdd->GetIsVisibleInInventory(); 
	NewItem.bIsConsumable = ItemToAdd->GetIsConsumable(); 
	ItemToAdd->Destroy();

	for (int i = 0; i < ItemArray.Num(); i++) // Try to find needed item to add additional count
	{
		if (ItemArray[i].ItemName == NewItem.ItemName)
		{
			ItemArray[i].CurrentCount = FMath::Clamp(ItemArray[i].CurrentCount + ItemsCount, 0, ItemStackMaxCount);
			return; 
		}
	}

	
	ItemArray.Add(NewItem);

}

void UInventoryComponent::GiveItem(TSubclassOf<AEquipableItem> ItemToAdd, uint8 ItemsCount)
{
	AEquipableItem* EquipableItem = GetWorld()->SpawnActor<AEquipableItem>(ItemToAdd); 
	uint8 ItemStackMaxCount = EquipableItem->GetStackMaxCount();
	FName ItemName = EquipableItem->GetItemName(); 

	//EquipableItem->Destroy(); 
	//EquipableItem = nullptr; 

	FInventoryItemSlotData NewItem;
	NewItem.ItemName = ItemName; 
	//NewItem.EquipedItem = EquipableItem;
	NewItem.CurrentCount = FMath::Clamp(ItemsCount, 0, ItemStackMaxCount);

	for (int i = 0; i < ItemArray.Num(); i++) // Try to find needed item to add additional count
	{
		if (ItemArray[i].ItemName == NewItem.ItemName)
		{
			ItemArray[i].CurrentCount = FMath::Clamp(ItemArray[i].CurrentCount + ItemsCount, 0, ItemStackMaxCount);
			//OnItemAdded.Broadcast(NewItem);
			return;
		}
	}

	//OnItemAdded.Broadcast(NewItem);
	ItemArray.Add(NewItem);
}

uint8 UInventoryComponent::RemoveItem(AEquipableItem* ItemToAdd)
{
	if (ItemArray.IsEmpty())
	{
		return 0; 
	}

	for (int i = 0; i < ItemArray.Num(); i++)
	{
		if (ItemArray[i].ItemName == ItemToAdd->GetItemName())
		{
			if (ItemArray[i].CurrentCount > 1)
			{
				ItemArray[i].CurrentCount -= 1;
				return ItemArray[i].CurrentCount;
			}
			else
			{
				ItemArray.RemoveAt(i);
				//ItemToAdd->Destroy();
				//ItemArray[i] = FInventoryItemSlotData{};
			}
			
		}
	}
	return 0;
}

bool UInventoryComponent::ContainsItem(FName ItemName)
{

	for (int i = 0; i < ItemArray.Num(); i++) 
	{
		if (ItemArray[i].ItemName == ItemName)
		{
			return true;
		}
	}

	return false; 
}

TArray<UBaseDocumentationData*> UInventoryComponent::GetDocumentationArray() const
{
	return DocumentationArray;	
}

void UInventoryComponent::SetDocumentationArray(TArray<UBaseDocumentationData*> NewDocsArray)
{
	DocumentationArray = NewDocsArray; 
}

TArray<UBaseDocumentationData*> UInventoryComponent::GetAllDocumentsOfType(EDocumentationType DocumentationType) const
{
	TArray<UBaseDocumentationData*> DocArray; 

	if (DocumentationArray.IsEmpty() || DocumentationType == EDocumentationType::None)
	{
		return DocArray;
	}


	switch (DocumentationType)
	{
	case EDocumentationType::Document:

		for (UBaseDocumentationData* CurrentDoc : DocumentationArray)
		{
			
			if (CurrentDoc->DocumentationType == EDocumentationType::Document)
			{
				DocArray.Add(CurrentDoc); 
			}
		}
		break;
	case EDocumentationType::Note:

		for (UBaseDocumentationData* CurrentDoc : DocumentationArray)
		{
			if (CurrentDoc->DocumentationType == EDocumentationType::Note)
			{
				DocArray.Add(CurrentDoc);
			}
		}

		break;
	case EDocumentationType::Picture:

		for (UBaseDocumentationData* CurrentDoc : DocumentationArray)
		{
			if (CurrentDoc->DocumentationType == EDocumentationType::Picture)
			{
				DocArray.Add(CurrentDoc);
			}
		}

		break;
	}

	return DocArray;
}


