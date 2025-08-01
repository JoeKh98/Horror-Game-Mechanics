// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Characters/DCBaseAICharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"

// Constructor: sets default values for this actor
ADCBaseAICharacter::ADCBaseAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach audio component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bEditableWhenInherited = true;
	AudioComponent->ComponentTags.Add("AudioComp");

	// Create and attach scene component to act as a socket for the camera
	FaceCameraSocket = CreateDefaultSubobject<USceneComponent>(TEXT("FaceCameraSocket"));
	FaceCameraSocket->SetupAttachment(RootComponent);

	// Create and attach camera component to the socket
	FaceCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FaceCamera"));
	FaceCamera->SetupAttachment(FaceCameraSocket);
	FaceCamera->bEditableWhenInherited = true;
	FaceCamera->ComponentTags.Add("FaceCamera");
}

// Called when the player interacts with this AI character
void ADCBaseAICharacter::Interact(ADCBaseCharacter* Character)
{
	OnInteract(Character);
}

// Returns the action event name (used for UI or input hints)
FName ADCBaseAICharacter::GetActionEventName() const
{
	return FName(); // Return empty name (can be overridden by child classes)
}

// Called when the game starts or when spawned
void ADCBaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADCBaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
