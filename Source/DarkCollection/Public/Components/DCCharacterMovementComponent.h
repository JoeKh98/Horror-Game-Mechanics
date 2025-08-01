// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DCCharacterMovementComponent.generated.h"

class UAttributesComponent; 

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UDCCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:


	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }	
	FORCEINLINE bool IsLeaning() const { return bIsLeaning; }
	//bool IsOnLadder() const;

	UFUNCTION(BlueprintCallable, Category = "Character movement | Sprint")
	bool IsOutOfStamina() const;


	void SetIsOutOfStamina(bool bIsOutOfStamina_In);

	void SetIsLeaning(bool bIsLeaning_In) { bIsLeaning = bIsLeaning_In; }
	void StartSprint();
	void StopSprint(); 

	virtual float GetMaxSpeed() const override; 



protected: 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement | Sprint", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SprintSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement | Stamina", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float OutOfStaminaSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement | Leaning", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float LeaningSpeed = 300.0f;

	UAttributesComponent* AttributesComponent; 

protected:

	class ADCBaseCharacter* GetBaseCharacterOwner() const;

private:

	bool bIsLeaning = false; 
	bool bIsSprinting = false; 
	bool bIsOutOfStamina = false;
	
};
