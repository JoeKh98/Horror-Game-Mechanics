// Fill out your copyright notice in the Description page of Project Settings.

//
//#include "Components/Events/DCEventActor.h"
//#include "Character/DCBaseCharacter.h"
//#include "Components/Attributes/AttributesComponent.h"
//#include "Character/Controller/DCBasePlayerController.h"
//
//#include <Kismet/GameplayStatics.h>
//#include <Kismet/KismetMathLibrary.h>
//#include <Camera/CameraComponent.h>
//
//
//// Sets default values for this component's properties
//ADCEventActor::ADCEventActor()
//{
//	PrimaryActorTick.bCanEverTick = true;
//	PrimaryActorTick.bStartWithTickEnabled = true; 
//}
//
//void ADCEventActor::CheckAndCreateEvents(FEvents& Event)
//{
//	if (!IsValid(Character))
//	{
//		return; 
//	}
//		
//	// TODO EnvironmentEvents
//	ExecuteDamageEvents(Event);
//	ExecuteLookAtActorEvents(Event); 
//
//}
//
//void ADCEventActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	TurnToActorTimeline.TickTimeline(DeltaTime);
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("gooooooooooooo"));
//
//}
//
//void ADCEventActor::BeginPlay()
//{
//	Character = Cast<ADCBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetOuter(), 0));
//	SetActorTickEnabled(true);
//
//}
//
//void ADCEventActor::ExecuteDamageEvents(FEvents& Event)
//{
//	if (Event.PlayerEvents.DamagePlayer.IsEmpty() || !IsValid(Character))
//	{
//		return;
//	}
//
//	for (auto DamageEvent : Event.PlayerEvents.DamagePlayer)
//	{
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.Owner = this; // Set the owner of the actor
//		SpawnParams.Instigator = GetInstigator(); // Set the instigator (optional)
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding; 
//		ADCEventActor* EventActor = GetWorld()->SpawnActor<ADCEventActor>(ADCEventActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
//		EventActor->ExecuteDamageEvent(DamageEvent);
//	}
//
//	
//}
//
//void ADCEventActor::ExecuteDamageEvent(FDamagePlayer& DamageEvent)
//{
//	Delay(DamageEvent.DelayBeforeAction, [DamageEvent, this]() {Character->GetCharacterAttributesComponent()->ApplyDamage(DamageEvent.DamageValue, Character); });	
//}
//
//void ADCEventActor::ExecuteLookAtActorEvents(FEvents& Event)
//{
//	if (Event.PlayerEvents.LookAtActor.IsEmpty() || !IsValid(Character) || !Character->GetCharacterAttributesComponent()->IsAlive())
//	{
//		return;
//	}
//
//	for (auto LookAtActorEvent : Event.PlayerEvents.LookAtActor)
//	{
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.Owner = this; 
//		SpawnParams.Instigator = GetInstigator(); 
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding; 
//		ADCEventActor* EventActor = GetWorld()->SpawnActor<ADCEventActor>(ADCEventActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
//		EventActor->ExecuteLookAtActorEvent(LookAtActorEvent); 
//	}
//}
//
//void ADCEventActor::ExecuteLookAtActorEvent(FLookAtActor& LookAtActorEvent)
//{
//	CurrentLookAtActorEvent = &LookAtActorEvent;
//
//	if (LookAtActorEvent.LookAtActorDetails.IsEmpty())
//	{
//		UE_LOG(LogTemp, Error, TEXT("LookAtActorDetails array is empty"));
//		return;
//	}
//
//	if (!bIsLookAtTimelineInitialized)
//	{
//		InitializeTimeline();
//	}
//	LookAtActorSequence(LookAtActorEvent);
//
//
//	/*Delay(LookAtActorEvent.DelayBeforeAction, [this, &LookAtActorEvent]()
//		{
//			if (!bIsLookAtTimelineInitialized)
//			{
//				InitializeTimeline();
//			}
//			LookAtActorSequence(LookAtActorEvent);
//		});*/
//
//}
//
//void ADCEventActor::LookAtActorSequence(FLookAtActor& LookAtActorEvent)
//{
//
//
//	if (!CurrentLookAtActorEvent || !IsValid(CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].ActorToLookAt))
//	{
//		return; 
//	}
//
//	UCameraComponent* CameraComponent = Character->FindComponentByClass<UCameraComponent>();
//	CameraCurrentRotation = CameraComponent->GetComponentRotation();
//	FVector CameraCurrentLocation = CameraComponent->GetComponentLocation();
//	FVector LookAtActorLocation = CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].ActorToLookAt->GetActorLocation();
//	LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraCurrentLocation, LookAtActorLocation); 
//
//	// TODO Add close widgets logic
//
//	if (CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve)
//	{
//		TurnToActorTimeline.SetPlayRate(CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].LookAtTurnSpeed);
//		TurnToActorTimeline.PlayFromStart(); 
//	}	
//
//
//}
//
//void ADCEventActor::Delay(float Seconds, TFunction<void()> FunctionToCall)
//{
//	
//	DelayTimerHandle.Invalidate(); 
//
//	GetWorld()->GetTimerManager().SetTimer(
//		DelayTimerHandle,
//		[FunctionToCall]()
//		{
//			if (FunctionToCall)
//			{
//				FunctionToCall();
//			}
//		},
//		Seconds,
//		false
//	);
//}
//
//void ADCEventActor::DestroyEventActor()
//{
//	// Add check for openning a level
//	//Delay(5.0f, [this]() { Destroy(); });
//}
//
//void ADCEventActor::OnTurnToActorTimelineTick(float Value)
//{
//	if (!Character || !Character->GetController())
//	{
//		UE_LOG(LogTemp, Error, TEXT("Character or Controller is null"));
//		return;
//	}
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("My float value: %f"), Value));
//
//	// Enable or disable input as needed
//	Character->SetIsLookingAt(true);
//	Character->SetPlayerInputStatus(false);
//
//	// Calculate new control rotation
//	FRotator NewControlRotation = UKismetMathLibrary::RLerp(CameraCurrentRotation, LookAtRotation, Value, true);
//
//	// Preserve the Roll component of the original rotation
//	NewControlRotation.Roll = Character->GetController()->GetControlRotation().Roll;
//
//	// Apply the new rotation
//	Character->GetController()->SetControlRotation(NewControlRotation);
//
//	// Log the new rotation for debugging
//	UE_LOG(LogTemp, Warning, TEXT("NewControlRotation: %s"), *NewControlRotation.ToString());
//
//	//Character->SetIsLookingAt(true); 
//	//Character->SetPlayerInputStatus(false);
//	//
//	//FRotator NewControlRotation = UKismetMathLibrary::RLerp(CameraCurrentRotation, LookAtRotation, Value, true);
//	//NewControlRotation.Roll = Character->GetController()->GetControlRotation().Roll; 
//	//Character->GetController()->SetControlRotation(NewControlRotation);
//}
//
//void ADCEventActor::OnTurnToActorTimelineFinished()
//{
//	//Delay(CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].LookAtDuration, [this]()
//	//	{
//	//		int LookAtActorDetailsLastIndex = CurrentLookAtActorEvent->LookAtActorDetails.Num() - 1;
//	//		if (LookAtActorDetailsLastIndex == LookAtCounter)
//	//		{
//	//			LookAtCounter = 0;
//	//			Character->SetPlayerInputStatus(true); 
//	//			Character->SetIsLookingAt(false); 
//	//			DestroyEventActor(); 
//	//		}
//	//		else
//	//		{
//	//			LookAtCounter += 1;
//	//			LookAtActorSequence(*CurrentLookAtActorEvent); 
//	//		}
//
//	//	});
//}
//
//void ADCEventActor::InitializeTimeline()
//{
//	bIsLookAtTimelineInitialized = true; 
//
//	FOnTimelineFloat TurnToActorInterpFunction; // Для изменения значений
//	FOnTimelineEvent TurnToActorTimelineFinished; // Для завершения таймлайна
//
//	TurnToActorInterpFunction.BindUFunction(this, FName("OnTurnToActorTimelineTick"));
//	TurnToActorTimelineFinished.BindUFunction(this, FName("OnTurnToActorTimelineFinished"));
//
//
//	if (CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve)
//	{
//		TurnToActorTimeline.AddInterpFloat(CurrentLookAtActorEvent->LookAtActorDetails[LookAtCounter].TurnToActorFloatCurve, TurnToActorInterpFunction);
//		TurnToActorTimeline.SetTimelineFinishedFunc(TurnToActorTimelineFinished);
//	}
//
//}
//
//
//
//

