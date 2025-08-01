// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Event/DCEventObject.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEventSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, uint8);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKCOLLECTION_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributesComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

////////////////////////////////////////////////////////// HEALTH ///////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	bool IsAlive();

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	void AddHealth(uint8 HealthToAdd);

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	void ApplyDamage(uint8 DamageAmount, AActor* DamageInstigator); 

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	uint8 GetHealth() const; 

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	void SetHealth(uint8 NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Health")
	uint8 GetHealthPercent() const; 

	UPROPERTY(BlueprintAssignable)
	FOnDeathEventSignature OnDeathEvent;

	FOnHealthChanged OnHealthChangedEvent;

////////////////////////////////////////////////////////// STAMINA ///////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina")
	void RestoreFullStamina();

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina")
	float GetCurrentStamina() const; 


////////////////////////////////////////////////////////// FLASHLIGHT ///////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Flashlight")
	void RestoreFlashlightBattery(); 

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Flashlight")
	float GetFlashlightRemainingBattery() const;

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Flashlight")
	void SetFlashlightRemainingBattery(float NewFlashlightRemainingBattery);

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Flashlight")
	void RechargeFlashlight();

////////////////////////////////////////////////////////// FEAR ///////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Fear")
	void Fear(FFearPlayer FearEvent);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Attributes | Health", meta = (UIMin = 0))
	uint8 MaxHealth = 3; // Hits number 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes | Stamina")
	float MaxStamina = 100.0f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes | Stamina")
	float StaminaRestoreSpeed = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes | Stamina")
	float StaminaSprintConsumption = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes | Flashlight")
	float MaxFlashlightBatteryCharge = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes | Flashlight")
	float FlashlightBatteryChargeConsumption = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline | Curve")
	UCurveFloat* FearTimelineFloat;


private: 

	UFUNCTION()
	void OnRep_Health();

	void OnHealthChanged();

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnFearTimelineUpdate(float Value); 

	UFUNCTION()
	void OnFearTimelineFinished();

	void UpdateStamina(float DeltaTime);

	void UpdateFlashlightBattery(float DeltaTime); 

	bool CanRestoreStamina();

private: 

	UPROPERTY()
	uint8 Health = 0;
	
	UPROPERTY()
	float CurrentStamina = 100.0f;

	UPROPERTY()
	UAudioComponent* CurrentFearSound = nullptr; 

	UPROPERTY()
	FTimeline FearTimeline; 

	UPROPERTY()
	class UCameraComponent* PlayerCamera = nullptr; 

	UPROPERTY()
	float CurrentFlashlightBatteryCharge = 100.0f;
	bool bCanRechargeFlashlight = false; 
	float CurrentFOV = 0.0f; 

	TWeakObjectPtr<class ADCBaseCharacter> CachedBaseCharacter;
};
