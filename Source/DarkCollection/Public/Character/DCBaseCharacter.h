// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "UObject/ScriptInterface.h"
#include "DCBaseCharacter.generated.h"

class IInteractable; 
class UInventoryComponent; 
class UAttributesComponent;
class UDCCharacterMovementComponent;

UENUM(BlueprintType)
enum class ELeanStatus : uint8
{
	LeanRight UMETA(DisplayName = "LeanRight"),
	LeanLeft UMETA(DisplayName = "LeanLeft"),
	None UMETA(DisplayName = "None")
};



UCLASS()
class DARKCOLLECTION_API ADCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:	

	ADCBaseCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay(); 

	virtual void MoveForward(float Value); 
	virtual void MoveRight(float Value);
	virtual void Turn(float Value);
	virtual void LookUp(float Value);

	virtual void Jump() override;
	
	virtual void ChangeCrouchState();
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override; 


	virtual void Interact();

	virtual void StartSprint();
	virtual void StopSprint();

	virtual void RightLeanStart();
	virtual void RightLeanStop();
	virtual void LeftLeanStart();
	virtual void LeftLeanStop();

	virtual void ChangeFlashlightState();
	void TurnOnFlashlight(); 
	void TurnOffFlashlight();
	virtual void PersonalRecordsMenu();

	virtual void NextEquipment();
	virtual void PrevEquipment();

	virtual void StartFocus();
	virtual void StopFocus();

	virtual void Menu();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetPlayerInputStatus(bool NewPlayerInput); 

	float GetAimingMovementSpeed() const;
	FORCEINLINE bool IsLookingAt() const { return bIsLookingAt; }
	FORCEINLINE bool IsAiming() const { return bIsAiming; }
	FORCEINLINE bool IsLeaning() const { return bIsLeaningRight || bIsLeaningLeft; }
	FORCEINLINE bool IsFlashlightOn() const { return bIsFlashlightOn; }
	FORCEINLINE bool CanUseFlashlight() const { return bIsFlashlightOn; }
	FORCEINLINE UInventoryComponent* GetCharacterInventoryComponent() const { return CharacterInventoryComponent; }
	FORCEINLINE UAttributesComponent* GetCharacterAttributesComponent() const { return AttributesComponent; }
	FORCEINLINE UDCCharacterMovementComponent* GetCharacterMovementComponent() const { return CharacterMovementComponent; }
	FORCEINLINE APlayerCameraManager* GetCharacterCameraManager() const { return PlayerCameraManager; }
	FORCEINLINE class ADCBasePlayerController* GetPlayerController() const { return PlayerController; }

	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	float GetMouseSensitivity() const;

	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	void SetMouseSensitivity(float NewMouseSensitivity);
	
	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	float IsInvertCameraH() const;

	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	float IsInvertCameraV() const;
	
	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	void IsInvertCameraHor(bool bIsInvertCameraH_In);
	
	UFUNCTION(BlueprintCallable, Category = "Character | Settings")
	void IsInvertCameraVer(bool bIsInvertCameraV_In);


	FORCEINLINE void SetIsLookingAt(bool bIsLookingAt_In) { bIsLookingAt = bIsLookingAt_In; } 
	//FORCEINLINE bool IsDead() const { return !GetCharacterAttributesComponent()->IsAlive(); }

	virtual void Tick(float DeltaTime) override;



protected: 

//////////////////////////////////////// CAMERA ////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Camera ")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Camera ")
	class USpringArmComponent* SpringArmComponent;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Camera | Settings")
	float MinCameraPitch = -50.0f;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Camera | Settings", meta = (UIMin = -90.0f, UIMax = 90.0f, ClampMin = -90.0f, ClampMax = 90.0f))
	float MaxCameraPitch = 50.0f;

//////////////////////////////////////// FLASHLIGHT ////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Flashlight ")
	class USpringArmComponent* FlashlightSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Flashlight ")
	class USpotLightComponent* Flashlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Flashlight ")
	float FlashlightIntensity = 20000.0f; 

//////////////////////////////////////// CROUCH ////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Crouch ")
	UCurveFloat* CrouchCurve;

	UFUNCTION()
	void UpdateCrouchTimeline(float Alpha);


//////////////////////////////////////// LEANING ////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Leaning ")
	float LeaningAmount = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Leaning ")
	float LeaningAngle = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Leaning ")
	UCurveFloat* LeanCurve;

	UFUNCTION()
	void UpdateLeanTimeline(float Alpha); 




//////////////////////////////////////// COMPONENTS ////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Components")
	UInventoryComponent* CharacterInventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Components")
	UAttributesComponent* AttributesComponent;

	UDCCharacterMovementComponent* CharacterMovementComponent;



	bool CanSprint();
	bool CanLean(ELeanStatus LeanStatus_In);
	bool CanUseFlashlight(); 

//////////////////////////////////////// INTERACT ////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Interact ")
	float LineOfSightDistance = 150.0f; 

	void TraceLineOfSight();

	UPROPERTY()
	TScriptInterface<IInteractable> LineOfSightObject; 

private:

	void TryChangeSprintState(float DeltaTime); 
	void UpdateCameraAngle(); 

private: 

	bool bIsLookingAt = false;
	bool bIsAiming = false; 
	bool bIsLeaning = false;
	bool bIsLeaningRight = false;
	bool bIsLeaningLeft = false; 
	bool bIsPersonalRecordsMenuOpened = false; 
	bool bIsSprintRequested = false;
	bool bIsFlashlightOn = false;
	//bool bIsCrouching = false; 


	bool bIsInvertCameraH = false;
	bool bIsInvertCameraV = false; 

	float CurrentAimingMovementSpeed = 800.0f; 
	float CrouchCapsuleStartSize;
	float CrouchCapsuleEndSize;
	float LeanStart;
	float LeanEnd;

	float MouseSensitivity = 1.0f; 
	
	FVector CachedCharacterRotation; 

	ELeanStatus LeanStatus = ELeanStatus::None; 



	FTimeline CrouchTimeline; 
	FOnTimelineFloat UpdateFunctionFloat;

	FTimeline LeanTimeline;
	
	UPROPERTY()
	APlayerCameraManager* PlayerCameraManager; 

	UPROPERTY()
	class ADCBasePlayerController* PlayerController; 

	UPROPERTY()
	class ADarkCollectionHUD* HUD; 

	UPROPERTY()
	class UUserWidget* PersonalRecordsMenuWidget;
};
