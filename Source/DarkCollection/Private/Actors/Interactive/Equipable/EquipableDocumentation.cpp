// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipableDocumentation.h"
#include "Components/StaticMeshComponent.h"
#include "Character/DCBaseCharacter.h"
#include "Components/Inventory/InventoryComponent.h"

AEquipableDocumentation::AEquipableDocumentation()
{
	// Create and attach the documentation mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DocumentationMesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AEquipableDocumentation::Interact(ADCBaseCharacter* Character)
{
	Super::Interact(Character);

	if (!IsValid(Character))
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableDocumentation::Interact - Character is not valid"));
		return;
	}

	// Get the inventory component from the character
	if (UInventoryComponent* InventoryComponent = Character->GetCharacterInventoryComponent())
	{
		// Add this documentation's asset to the character's inventory
		InventoryComponent->AddDocumentation(DocumentAsset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEquipableDocumentation::Interact - InventoryComponent is null"));
	}

	// Destroy the documentation actor after it's picked up
	Destroy();
}