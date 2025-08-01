// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Interactive/InteractableObject.h"
#include "DarkCollectionTypes.h"
#include "Character/DCBaseCharacter.h"
#include "GameInstances/DCBaseGameInstance.h"
#include "SaveSystem/DCSaveComponent.h"
#include "Actors/Event/DCEventObject.h"
#include "GameModes/DCBaseGameMode.h"

// Constructor: sets this actor to tick every frame
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the player interacts with the object
void AInteractableObject::Interact(ADCBaseCharacter* Character)
{
	if (!IsValid(Character))
	{
		return;
	}

	// Triggers events associated with the Interact type
	CheckEvents(EEventType::Interact);
}

// Returns the name of the interaction action (used in UI or bindings)
FName AInteractableObject::GetActionEventName() const
{
	return ActionInteract;
}

// Called when the game starts or when the object is spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Checks all configured events and executes those whose conditions are met
void AInteractableObject::CheckEvents(EEventType EventType)
{
	// First pass: evaluate which events should be triggered
	for (int i = 0; i < Events.Num(); i++)
	{
		if (Events[i].TriggerEventType == EventType)
		{
			Events[i].Counter += 1;

			// Check if the event should trigger after N times
			if (Events[i].AfterNTimes == Events[i].Counter)
			{
				IndexCache.Add(i);

				// If the event can be repeated, reset the counter
				if (!Events[i].bDoOnce)
				{
					Events[i].Counter = 0;
				}
			}
		}
	}

	// Second pass: execute the events whose conditions were met
	for (int i = 0; i < IndexCache.Num(); i++)
	{
		// Save the game if required
		if (Events[i].ShouldAutosave)
		{
			Cast<UDCBaseGameInstance>(GetGameInstance())->GetSaveComponent()->SaveGame(FText::FromString("Name"));
		}

		// Spawn a temporary event actor to handle this event
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);

		// Pass the event data to the spawned event actor
		EventActor->CheckAndCreateEvents(Events[i].Events);
	}
}
