// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Event/DCEventObject.h"
#include "FunctionLibraries/DCFunctionLibrary.h"
#include "Character/DCBaseCharacter.h"
#include "Components/Attributes/AttributesComponent.h"
#include "SaveSystem/DCSaveGame.h"
#include "Character/Controller/DCBasePlayerController.h"
#include "Components/Inventory/InventoryComponent.h"
#include "GameInstances/DCBaseGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "SaveSystem/DCSaveComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Camera/CameraComponent.h>


// Sets default values for this actor's properties
ADCEventObject::ADCEventObject()
{
	// Enable ticking every frame
	PrimaryActorTick.bCanEverTick = true;
}

// Entry point for handling and executing all incoming events
void ADCEventObject::CheckAndCreateEvents(FEvents& Event)
{
	if (!IsValid(Character))
	{
		return;
	}

	// Execute environment-related events
	ExecuteTransformEvents(Event);
	ExecuteSpawnActorEvents(Event);
	ExecuteVisualEvents(Event);

	// Execute player-related events
	ExecuteDamageEvents(Event);
	ExecuteLookAtActorEvents(Event);
	ExecuteFearEvents(Event);

	// Execute level-related events
	ExecuteLevelEvents(Event);

	// Execute audio-related events
	Execute2DSoundEvents(Event);

	// Destroy this event actor after processing all events
	DestroyEventActor();
}

// Called when the actor is first initialized
void ADCEventObject::BeginPlay()
{
	Super::BeginPlay();

	// Cache reference to the player character
	Character = Cast<ADCBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetOuter(), 0));
}

// Called every frame
void ADCEventObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update timelines used for animations or effects
	TurnToActorTimeline.TickTimeline(DeltaTime);
}

// Executes all actor spawn events defined in the event data
void ADCEventObject::ExecuteSpawnActorEvents(FEvents Event)
{
	if (Event.EnvironmentEvents.SpawnActors.IsEmpty() || !IsValid(Character))
	{
		return;
	}

	for (auto SpawnActorEvent : Event.EnvironmentEvents.SpawnActors)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		EventActor->ExecuteSpawnActorEvent(SpawnActorEvent);
	}
}

// Spawns a single actor based on event settings
void ADCEventObject::ExecuteSpawnActorEvent(FSpawnActors SpawnActorEvent)
{
	Delay(SpawnActorEvent.DelayBeforeAction, [this, SpawnActorEvent]()
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			SpawnParams.SpawnCollisionHandlingOverride = SpawnActorEvent.CollisionHandlingMethod;

			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
				SpawnActorEvent.SpawnActorClass,
				SpawnActorEvent.SpawnActorTransform,
				SpawnParams
			);

			if (!IsValid(SpawnedActor))
			{
				return;
			}

			// Apply tags
			if (SpawnActorEvent.SpawnedActorTags.IsValidIndex(0))
			{
				SpawnedActor->Tags = SpawnActorEvent.SpawnedActorTags;
			}

			// Handle actor attachment
			if (IsValid(SpawnActorEvent.AttachTo.AttachToActor))
			{
				UPrimitiveComponent* AttachComp = Cast<UPrimitiveComponent>(
					SpawnActorEvent.AttachTo.AttachToActor->GetComponentsByTag(
						UPrimitiveComponent::StaticClass(),
						SpawnActorEvent.AttachTo.ParentComponentByTag
					)[0]
				);

				if (IsValid(AttachComp))
				{
					FAttachmentTransformRules AttachmentTransformRules(
						SpawnActorEvent.AttachTo.LocationAttachmentRule,
						SpawnActorEvent.AttachTo.RotationAttachmentRule,
						SpawnActorEvent.AttachTo.ScaleAttachmentRule,
						true
					);
					SpawnedActor->AttachToComponent(AttachComp, AttachmentTransformRules);
				}
			}

			DestroyEventActor();
		});
}


// Executes all visual events that affect actors' appearance or existence
void ADCEventObject::ExecuteVisualEvents(FEvents Event)
{
	if (Event.EnvironmentEvents.ActorsVisualOperations.IsEmpty() || !IsValid(Character))
	{
		return;
	}

	for (auto VisualEvent : Event.EnvironmentEvents.ActorsVisualOperations)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		EventActor->ExecuteVisualEvent(VisualEvent);
	}
}

// Applies visibility or destruction changes to target actors
void ADCEventObject::ExecuteVisualEvent(FActorsVisualOperations VisualEvent)
{
	// Handle direct actor references
	if (VisualEvent.Actors.IsValidIndex(0))
	{
		Delay(VisualEvent.DelayBeforeActions, [this, VisualEvent]()
			{
				if (VisualEvent.bIsDestroyActor)
				{
					for (AActor* CurrentActor : VisualEvent.Actors)
					{
						CurrentActor->Destroy();
					}
				}
				else
				{
					for (AActor* CurrentActor : VisualEvent.Actors)
					{
						CurrentActor->SetActorHiddenInGame(VisualEvent.bIsHiddenInGame);
						CurrentActor->SetActorEnableCollision(!VisualEvent.bIsDisableCollision);
					}
				}

				DestroyEventActor();
			});
	}

	// Handle actors by tags
	if (VisualEvent.GetAllActorsWithTags.IsValidIndex(0))
	{
		Delay(VisualEvent.DelayBeforeActions, [this, VisualEvent]()
			{
				TArray<AActor*> ActorsWithTags;
				for (FName CurrentTag : VisualEvent.GetAllActorsWithTags)
				{
					UGameplayStatics::GetAllActorsWithTag(GetWorld(), CurrentTag, ActorsWithTags);

					if (VisualEvent.bIsDestroyActor)
					{
						for (AActor* CurrentActor : ActorsWithTags)
						{
							CurrentActor->Destroy();
						}
					}
					else
					{
						for (AActor* CurrentActor : ActorsWithTags)
						{
							CurrentActor->SetActorHiddenInGame(VisualEvent.bIsHiddenInGame);
							CurrentActor->SetActorEnableCollision(!VisualEvent.bIsDisableCollision);
						}
					}
				}

				DestroyEventActor();
			});
	}
}


// Executes all damage events targeting the player character
void ADCEventObject::ExecuteDamageEvents(FEvents& Event)
{
	if (Event.PlayerEvents.DamagePlayer.IsEmpty() || !IsValid(Character))
	{
		return;
	}

	for (auto DamageEvent : Event.PlayerEvents.DamagePlayer)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		EventActor->ExecuteDamageEvent(DamageEvent);
	}
}

// Applies damage to the player after delay
void ADCEventObject::ExecuteDamageEvent(FDamagePlayer& DamageEvent)
{
	Delay(DamageEvent.DelayBeforeAction, [DamageEvent, this]()
		{
			Character->GetCharacterAttributesComponent()->ApplyDamage(DamageEvent.DamageValue, Character);
		});
}

// Executes all "look at" events (player camera forced to look at actor)
void ADCEventObject::ExecuteLookAtActorEvents(FEvents& Event)
{
	if (Event.PlayerEvents.LookAtActor.IsEmpty() || !IsValid(Character) || !Character->GetCharacterAttributesComponent()->IsAlive())
	{
		return;
	}

	for (auto LookAtActorEvent : Event.PlayerEvents.LookAtActor)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		EventActor->ExecuteLookAtActorEvent(LookAtActorEvent);
	}
}

// Begins timeline for "look at actor" logic
void ADCEventObject::ExecuteLookAtActorEvent(FLookAtActor LookAtActorEvent)
{
	CurrentLookAtActorEvent = LookAtActorEvent;

	if (LookAtActorEvent.LookAtActorDetails.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LookAtActorDetails array is empty"));
		return;
	}

	Delay(LookAtActorEvent.DelayBeforeAction, [this]()
		{
			if (!bIsLookAtTimelineInitialized)
			{
				InitializeLookAtTimeline();
			}
			LookAtActorSequence(CurrentLookAtActorEvent);
		});
}

void ADCEventObject::LookAtActorSequence(FLookAtActor LookAtActorEvent)
{
	// Store the current LookAt event data
	CurrentLookAtActorEvent = LookAtActorEvent;

	// Validate the current index in the LookAt details array
	if (!CurrentLookAtActorEvent.LookAtActorDetails.IsValidIndex(LookAtCounter))
	{
		return;
	}

	// Get the player's camera component
	UCameraComponent* CameraComponent = Character->FindComponentByClass<UCameraComponent>();
	CameraCurrentRotation = CameraComponent->GetComponentRotation();
	FVector CameraCurrentLocation = CameraComponent->GetComponentLocation();

	// Calculate the target location and the desired look-at rotation
	FVector LookAtActorLocation = CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].ActorToLookAt->GetActorLocation();
	LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraCurrentLocation, LookAtActorLocation);

	// TODO: Add logic to close any currently open UI widgets

	// If a look-at curve is defined, begin rotating the camera using a timeline
	if (CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve)
	{
		// Set the timeline play rate based on event data
		TurnToActorTimeline.SetPlayRate(CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].LookAtTurnSpeed);

		// Disable player input during the look-at sequence
		Character->SetPlayerInputStatus(false);

		// Start the timeline from the beginning
		TurnToActorTimeline.PlayFromStart();
	}
}


void ADCEventObject::ExecuteFearEvents(FEvents& Event)
{
	// Check if there are fear events and the character is valid and alive
	if (Event.PlayerEvents.FearPlayer.IsEmpty() || !IsValid(Character) || !Character->GetCharacterAttributesComponent()->IsAlive())
	{
		return;
	}

	// Iterate over all fear events and trigger them via new spawned event actors
	for (const auto& FearEvent : Event.PlayerEvents.FearPlayer)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		EventActor->ExecuteFearEvent(FearEvent);
	}
}

void ADCEventObject::ExecuteFearEvent(FFearPlayer FearEvent)
{
	// Delay before applying the fear effect to the character
	Delay(FearEvent.DelayBeforeAction, [FearEvent, this]() {
		Character->GetCharacterAttributesComponent()->Fear(FearEvent);
		});
}

void ADCEventObject::ExecuteLevelEvents(FEvents& Event)
{
	// If the event specifies to open a new level
	if (Event.LevelEvents.OpenLevel.bShouldOpenLevel)
	{
		Delay(Event.LevelEvents.OpenLevel.DelayBeforeAction, [this, Event]()
			{
				// Save inventory if needed
				if (Event.LevelEvents.OpenLevel.bShouldKeepInventory)
				{
					FInventorySaveInfo NewSaveInfo;
					NewSaveInfo.ItemArray = Character->GetCharacterInventoryComponent()->GetItemsArray();
					NewSaveInfo.DocumentationArray = Character->GetCharacterInventoryComponent()->GetDocumentationArray();

					UDCBaseGameInstance* GameInstance = Cast<UDCBaseGameInstance>(GetGameInstance());
					GameInstance->InventoryAndDocsCache = NewSaveInfo;
					GameInstance->bIsNewLevel = true;
				}

				// Open the specified level
				UGameplayStatics::OpenLevel(GetWorld(), Event.LevelEvents.OpenLevel.LevelName);

				// Load streaming levels if any
				if (!Event.LevelEvents.LoadSteamLevels.IsEmpty() && IsValid(Character))
				{
					for (const auto& LoadStreamLevel : Event.LevelEvents.LoadSteamLevels)
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
						SpawnParams.Instigator = GetInstigator();
						SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

						ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
							ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
						EventActor->LoadStream(LoadStreamLevel);
					}
				}

				// Unload streaming levels if any
				if (!Event.LevelEvents.UnloadSteamLevels.IsEmpty() && IsValid(Character))
				{
					for (const auto& UnloadStreamLevel : Event.LevelEvents.UnloadSteamLevels)
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
						SpawnParams.Instigator = GetInstigator();
						SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

						ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
							ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
						EventActor->UnloadStream(UnloadStreamLevel);
					}
				}
			});
	}
}

void ADCEventObject::LoadStream(FLoadStream LoadStream)
{
	// Delay before loading streaming level
	Delay(LoadStream.DelayBeforeAction, [this, LoadStream]()
		{
			UGameplayStatics::LoadStreamLevel(
				GetWorld(), LoadStream.LevelName, LoadStream.bIsMakeVisibleAfterLoad,
				LoadStream.bShouldBlockAfterLoad, FLatentActionInfo());

			Cast<UDCBaseGameInstance>(UGameplayStatics::GetGameInstance(this))
				->GetSaveComponent()->CollectStreaming(LoadStream.LevelName, true);
		});
}

void ADCEventObject::UnloadStream(FUnloadStream UnloadStream)
{
	// Unload the streaming level immediately
	UGameplayStatics::UnloadStreamLevel(GetWorld(), UnloadStream.LevelName, FLatentActionInfo(), false);

	Cast<UDCBaseGameInstance>(UGameplayStatics::GetGameInstance(this))
		->GetSaveComponent()->CollectStreaming(UnloadStream.LevelName, false);
}

void ADCEventObject::Execute2DSoundEvents(FEvents& Events)
{
	// Check for valid sound events and character
	if (Events.SoundEvents.Play2DSound.IsEmpty() || !IsValid(Character))
	{
		return;
	}

	// Trigger each 2D sound event using a new actor instance
	for (const auto& SoundEvent : Events.SoundEvents.Play2DSound)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ADCEventObject* EventActor = GetWorld()->SpawnActor<ADCEventObject>(
			ADCEventObject::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		EventActor->Execute2DSoundEvent(SoundEvent);
	}
}

void ADCEventObject::Execute2DSoundEvent(FPlay2DSound SoundEvent)
{
	// Validate the sound asset
	if (!IsValid(SoundEvent.Sound))
	{
		DestroyEventActor();
		return;
	}

	// Delay before playing the sound
	Delay(SoundEvent.DelayBeforeAction, [SoundEvent, this]()
		{
			UDCFunctionLibrary::Play2DSound(this, SoundEvent.Sound);
			DestroyEventActor();
		});
}


void ADCEventObject::Delay(float Seconds, TFunction<void()> FunctionToCall)
{
	// Clear any existing timer
	DelayTimerHandle.Invalidate();

	// Set a new timer to execute the function after a delay
	GetWorld()->GetTimerManager().SetTimer(
		DelayTimerHandle,
		[FunctionToCall]()
		{
			if (FunctionToCall)
			{
				FunctionToCall();
			}
		},
		Seconds,
		false
	);
}

void ADCEventObject::DestroyEventActor()
{
	// Delayed self-destruction to allow timeline or delayed actions to finish
	Delay(5.0f, [this]() { Destroy(); });
}

void ADCEventObject::OnTurnToActorTimelineTick(float Value)
{
	// Validate character and its controller
	if (!Character || !Character->GetController())
	{
		UE_LOG(LogTemp, Error, TEXT("Character or Controller is null"));
		return;
	}

	// Show debug message with current timeline value
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("My float value: %f"), Value));

	// Enable look-at state
	Character->SetIsLookingAt(true);

	// Interpolate rotation between current and target
	FRotator NewControlRotation = UKismetMathLibrary::RLerp(CameraCurrentRotation, LookAtRotation, Value, true);

	// Preserve camera roll
	NewControlRotation.Roll = Character->GetController()->GetControlRotation().Roll;

	// Apply new control rotation
	Character->GetController()->SetControlRotation(NewControlRotation);

	// Log applied rotation
	UE_LOG(LogTemp, Warning, TEXT("NewControlRotation: %s"), *NewControlRotation.ToString());
}

void ADCEventObject::OnTurnToActorTimelineFinished()
{
	// Wait for the desired look-at duration, then continue or finish the sequence
	float DelayTime = CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].LookAtDuration;

	DelayTimerHandle.Invalidate();

	GetWorld()->GetTimerManager().SetTimer(
		DelayTimerHandle,
		this,
		&ADCEventObject::KeepLooking,
		DelayTime,
		false
	);
}

void ADCEventObject::InitializeLookAtTimeline()
{
	bIsLookAtTimelineInitialized = true;

	// Bind timeline update and finished functions
	FOnTimelineFloat TurnToActorInterpFunction;
	FOnTimelineEvent TurnToActorTimelineFinished;

	TurnToActorInterpFunction.BindUFunction(this, FName("OnTurnToActorTimelineTick"));
	TurnToActorTimelineFinished.BindUFunction(this, FName("OnTurnToActorTimelineFinished"));

	// Add float curve and setup finish callback
	if (CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve)
	{
		TurnToActorTimeline.AddInterpFloat(
			CurrentLookAtActorEvent.LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve,
			TurnToActorInterpFunction);

		TurnToActorTimeline.SetTimelineFinishedFunc(TurnToActorTimelineFinished);
	}
}

void ADCEventObject::KeepLooking()
{
	// Check if we reached the end of the look-at sequence
	int32 LastIndex = CurrentLookAtActorEvent.LookAtActorDetails.Num() - 1;
	if (LookAtCounter == LastIndex)
	{
		// End sequence
		LookAtCounter = 0;
		Character->SetPlayerInputStatus(true);
		Character->SetIsLookingAt(false);
		DestroyEventActor();
	}
	else
	{
		// Proceed to next target
		LookAtCounter++;
		LookAtActorSequence(CurrentLookAtActorEvent);
	}
}

void ADCEventObject::InitializeTransformTimeline()
{
	bIsTransformTimelineInitialized = true;

	// Bind timeline update and finished functions
	FOnTimelineFloat TransformActorInterpFunction;
	FOnTimelineEvent TransformActorTimelineFinished;

	TransformActorInterpFunction.BindUFunction(this, FName("OnTransformActorTimelineUpdate"));
	TransformActorTimelineFinished.BindUFunction(this, FName("OnTransformActorTimelineFinished"));

	// Add curve and set finish function
	if (CurrentTransformEvent.TransformDetails[TransformSequenceCounter].TransformCurveFloat)
	{
		ActorTransformTimeline.AddInterpFloat(
			CurrentTransformEvent.TransformDetails[TransformSequenceCounter].TransformCurveFloat,
			TransformActorInterpFunction);

		ActorTransformTimeline.SetTimelineFinishedFunc(TransformActorTimelineFinished);
	}
}

void ADCEventObject::OnTransformActorTimelineUpdate(float Value)
{
	// Interpolate transform based on curve value
	FTransform NewTransform = UKismetMathLibrary::TLerp(
		ActorCurrentTransform,
		CurrentTransformEvent.TransformDetails[TransformSequenceCounter].TransformTo,
		Value);

	CurrentTransformEvent.TransformActor->SetActorTransform(NewTransform);
}

void ADCEventObject::OnTransformActorTimelineFinished()
{
	// Move to next transform in sequence or end
	if (TransformSequenceCounter == CurrentTransformEvent.TransformDetails.Num() - 1)
	{
		TransformSequenceCounter = 0;
		DestroyEventActor();
	}
	else
	{
		TransformSequenceCounter++;
		ActorTransformSequence(CurrentTransformEvent);
	}
}





