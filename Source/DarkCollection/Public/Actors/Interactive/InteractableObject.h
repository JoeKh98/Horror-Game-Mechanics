// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Interactive/Interface/Interactive.h"
#include "Actors/Event/DCEventObject.h"
#include "InteractableObject.generated.h"

class ADCBaseCharacter; 

UCLASS()
class DARKCOLLECTION_API AInteractableObject : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();


	 
	virtual void Interact(ADCBaseCharacter* Character) override;
	virtual FName GetActionEventName() const override; 




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract(ADCBaseCharacter* Character); 


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void CheckEvents(EEventType EventType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event", meta = (DisplayName = "Add New Event"))
	TArray<FEventsManager> Events; 

private: 

	UPROPERTY()
	TArray<int> IndexCache; 



	bool bHasInteractEvent = false;

};
