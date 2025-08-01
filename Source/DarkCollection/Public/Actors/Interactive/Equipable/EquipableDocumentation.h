// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractableObject.h"
#include "../DarkCollectionTypes.h"
#include "EquipableDocumentation.generated.h"




/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API AEquipableDocumentation : public AInteractableObject
{
	GENERATED_BODY()


public:

	AEquipableDocumentation(); 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	EDocumentationType DocumentationType = EDocumentationType::None; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	class UBaseDocumentationData* DocumentAsset;

	virtual void Interact(ADCBaseCharacter* Character) override;

protected: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh; 
};
