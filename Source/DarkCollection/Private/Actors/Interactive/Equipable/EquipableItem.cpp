#include "Actors/Interactive/Equipable/EquipableItem.h"
#include "Character/DCBaseCharacter.h"
#include "Data/EquipableItems/EquipableItemsDT.h"
#include "Components/Inventory/InventoryComponent.h"

AEquipableItem::AEquipableItem()
{
	// Create and attach the item mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	Mesh->SetupAttachment(RootComponent);

	// Assign a unique ID based on the object name
	ItemID = GetFName().ToString();
}

void AEquipableItem::Interact(ADCBaseCharacter* Character)
{
	Super::Interact(Character);

	if (!IsValid(Character))
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableItem::Interact - Character is not valid"));
		return;
	}

	// Get inventory component from the character
	UInventoryComponent* InventoryComponent = Character->GetCharacterInventoryComponent();

	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableItem::Interact - InventoryComponent is null"));
		return;
	}

	// Assign item ownership and add item to the inventory
	this->ItemOwner = Character;
	InventoryComponent->AddItem(this, this->NumberOfItemsToAddInventory);
}

void AEquipableItem::Consume_Implementation()
{
	// This function is meant to be overridden by Blueprints or derived classes
}

uint8 AEquipableItem::GetStackMaxCount() const
{
	uint8 StackMaxCount = 1;

	if (ItemData.DataTable)
	{
		static const FString ContextString(TEXT("GENERAL")); // Used for logging

		FEquipableItemsDT* DataRow = ItemData.DataTable->FindRow<FEquipableItemsDT>(ItemData.RowName, ContextString);

		if (DataRow)
		{
			StackMaxCount = DataRow->ItemMaxCount;
			UE_LOG(LogTemp, Log, TEXT("ItemMaxCount: %d"), StackMaxCount);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AEquipableItem::GetStackMaxCount - Row not found for %s"), *ItemData.RowName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableItem::GetStackMaxCount - DataTable is null"));
	}

	return StackMaxCount;
}

FName AEquipableItem::GetItemName() const
{
	FName ItemName = FName("None");

	if (ItemData.IsNull())
	{
		return ItemName;
	}

	if (ItemData.DataTable)
	{
		ItemName = ItemData.RowName;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableItem::GetItemName - DataTable is null"));
	}

	return ItemName;
}

bool AEquipableItem::GetIsConsumable() const
{
	return bIsConsumable;
}

bool AEquipableItem::GetIsVisibleInInventory() const
{
	return bIsVisibleInInventory;
}

FString AEquipableItem::GetItemID() const
{
	return ItemID;
}
