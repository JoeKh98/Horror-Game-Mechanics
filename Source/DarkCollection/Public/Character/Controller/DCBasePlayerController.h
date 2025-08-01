// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DCBasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API ADCBasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ADCBasePlayerController();

	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void PersonalRecordsMenu();

protected:

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnHealthAttributeChanged")
	void BP_OnHealthAttributeChanged(float OldHealth, float NewHealth, AActor* Causer);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnTakeDamage")
	void OnTakeDamage(const float DamageAmount, AActor* Causer);

	UPROPERTY(BlueprintReadOnly)
	bool IsInInventory = false;

	UPROPERTY(BlueprintReadOnly)
	bool IsInPersonalRecordsMenu = false;

private: 
	
	void MoveForward(float Value);
	void MoveRight(float Value); 
	void Turn(float Value);
	void LookUp(float Value); 

	void Jump(); 
	void ChangeCrouchState(); 
	void Interact(); 

	void StartSprint(); 
	void StopSprint(); 

	void RightLeanStart(); 
	void RightLeanStop(); 
	void LeftLeanStart(); 
	void LeftLeanStop(); 

	void ChangeFlashlightState();

	void NextEquipment();
	void PrevEquipment(); 

	void StartFocus(); 
	void StopFocus(); 

	void Menu(); 
	void Inventory(); 

	TSoftObjectPtr<class ADCBaseCharacter> CachedBaseCharacter; 
	class UUserWidget* PersonalRecordsMenuWidget;
	class UUserWidget* InventoryWidget;


};
