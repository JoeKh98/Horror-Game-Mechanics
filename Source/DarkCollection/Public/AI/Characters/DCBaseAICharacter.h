// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Interactive/Interface/Interactive.h"
#include "DCBaseAICharacter.generated.h"

UCLASS()
class DARKCOLLECTION_API ADCBaseAICharacter : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCBaseAICharacter();

	virtual void Interact(ADCBaseCharacter* Character) override;
	virtual FName GetActionEventName() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract(ADCBaseCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Audio ")
	class UAudioComponent* AudioComponent; 

	UPROPERTY(EditAnywhere, Category = "AI | Face Camera")
	class USceneComponent* FaceCameraSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Face Camera")
	class UCameraComponent* FaceCamera; 

public:	

	virtual void Tick(float DeltaTime) override;


private:

};
