// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DCBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/DCCharacterMovementComponent.h"
#include "Character/Controller/DCBasePlayerController.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "UI/HUD/DarkCollectionHUD.h"
#include <Kismet/GameplayStatics.h>
#include "Actors/Interactive/Interface/Interactive.h"
#include "Components/SpotLightComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Components/Attributes/AttributesComponent.h"



ADCBaseCharacter::ADCBaseCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	CharacterMovementComponent = StaticCast<UDCCharacterMovementComponent*>(GetCharacterMovement());

	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent); 
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraRotationLag = true; 
	SpringArmComponent->CameraRotationLagSpeed = 10.0f; 


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent); 
	FlashlightSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Flashlight Spring Arm"));
	FlashlightSpringArmComponent->SetupAttachment(CameraComponent);
	FlashlightSpringArmComponent->SetRelativeLocation(FVector(10.0f, 30.0f, -40.0f)); 
	FlashlightSpringArmComponent->bEnableCameraRotationLag = true;
	FlashlightSpringArmComponent->CameraRotationLagSpeed = 10.0f;
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FlashlightSpringArmComponent);
	Flashlight->SetHiddenInGame(true);





	UGameplayStatics::GetPlayerController(this, 0);
	PlayerController = Cast<ADCBasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	CharacterInventoryComponent = CreateAbstractDefaultSubobject<UInventoryComponent>(TEXT("CharacterInventory"));
	AttributesComponent = CreateAbstractDefaultSubobject<UAttributesComponent>(TEXT("CharacterAttributes"));
	
}

void ADCBaseCharacter::BeginPlay()
{
	Super::BeginPlay(); 

	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	HUD = StaticCast<ADarkCollectionHUD*>(PlayerController->GetHUD());
	

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMin = MinCameraPitch; 
		PlayerCameraManager->ViewPitchMax = MaxCameraPitch;
	}



	if (IsValid(CrouchCurve))
	{
		//FOnTimelineFloatStatic PlatformMovementTimelineUpdate;
		//PlatformMovementTimelineUpdate.BindUObject(this, &ADCBaseCharacter::UpdateCrouchTimeline);
		UpdateFunctionFloat.BindDynamic(this, &ADCBaseCharacter::UpdateCrouchTimeline);
		CrouchTimeline.AddInterpFloat(CrouchCurve, UpdateFunctionFloat); 

		CrouchCapsuleStartSize = GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); 
		CrouchCapsuleEndSize = CrouchCapsuleStartSize / 2; 
	}

	if (IsValid(LeanCurve))
	{
		FOnTimelineFloatStatic LeanTimelineUpdate;
		LeanTimelineUpdate.BindUObject(this, &ADCBaseCharacter::UpdateLeanTimeline); 
		LeanTimeline.AddInterpFloat(LeanCurve, LeanTimelineUpdate); 
	}

}

void ADCBaseCharacter::MoveForward(float Value)
{
	if ((GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()) && !FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void ADCBaseCharacter::MoveRight(float Value)
{
	if ((GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()) && !FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f); 
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value); 
	}
}

void ADCBaseCharacter::Turn(float Value)
{	
	bIsInvertCameraH ? AddControllerYawInput(Value * MouseSensitivity * -1.0f) : AddControllerYawInput(Value * MouseSensitivity);

	if (bIsLeaning)
	{
		float DotProduct = FVector::DotProduct(CachedCharacterRotation, GetActorForwardVector());

		if (DotProduct < 0.80)
		{
			if (bIsLeaningRight)
			{
				RightLeanStop();
			}
			if (bIsLeaningLeft)
			{
				LeftLeanStop();
			}
		}

		if (/*PlayerController->IsInputKeyDown(EKeys::E) && */!LeanTimeline.IsPlaying())
		{
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this); // Ignore self
			bool bHit = GetWorld()->SweepSingleByObjectType(
				HitResult,
				CameraComponent->GetComponentLocation(),
				CameraComponent->GetComponentLocation(),
				FQuat::Identity,
				FCollisionObjectQueryParams::AllObjects,
				FCollisionShape::MakeSphere(10.0f),
				CollisionParams);
		
			DrawDebugSphere(
				GetWorld(),
				HitResult.Location,
				10.0f,
				12,
				FColor::Green,
				true);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, bHit ? TEXT("HIT") : TEXT("UNHIT"));
		
			if (bHit)
			{
				if (bIsLeaningRight)
				{
					RightLeanStop();
				}
				if (bIsLeaningLeft)
				{
					LeftLeanStop();
				}
			}
		}


	}
}

void ADCBaseCharacter::LookUp(float Value)
{
	bIsInvertCameraV ? AddControllerPitchInput(Value * MouseSensitivity * -1.0f) : AddControllerPitchInput(Value * MouseSensitivity);
}

void ADCBaseCharacter::Jump()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		UnCrouch(); 
	}
	//else
	//{
	//	Super::Jump();
	//}
	
}

void ADCBaseCharacter::ChangeCrouchState()
{
	if (GetCharacterMovement()->IsCrouching() && !CrouchTimeline.IsPlaying())
	{
		UnCrouch();

	}
	else if(!CrouchTimeline.IsPlaying())
	{
		Crouch();
	}
}

void ADCBaseCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	AddActorLocalOffset(FVector(0.0f, 0.0f, 50.0f));
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);	
	if (CrouchCurve)
	{
		if (!CrouchTimeline.IsPlaying())
		{
			CrouchTimeline.Play();
		}
		else
		{
			CrouchTimeline.PlayFromStart();
		}
		
	}

	
}

void ADCBaseCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	if (CrouchCurve)
	{
		if (CrouchTimeline.IsPlaying())
		{

			//AddActorLocalOffset(FVector(0.0f, 0.0f, 5.0f));
			RecalculateCrouchedEyeHeight();
			CrouchTimeline.Reverse();

		}
		else
		{
			CrouchTimeline.ReverseFromEnd();
		}
		
	}
	

}

void ADCBaseCharacter::Interact()
{
	if (LineOfSightObject.GetInterface())
	{
		LineOfSightObject->Interact(this); 
	}
}

void ADCBaseCharacter::StartSprint()
{
	bIsSprintRequested = true;
	if (bIsCrouched)
	{
		UnCrouch();
	}
}

void ADCBaseCharacter::StopSprint()
{
	bIsSprintRequested = false;
}

void ADCBaseCharacter::RightLeanStart()
{
	if (!CanLean(ELeanStatus::LeanRight))
	{
		return; 
	}

	CachedCharacterRotation = SpringArmComponent->GetForwardVector(); 
	LeaningAmount = FMath::Abs(LeaningAmount);
	LeaningAngle = FMath::Abs(LeaningAngle);;
	LeanTimeline.Play(); 
	bIsLeaning = bIsLeaningRight = true;
	CharacterMovementComponent->SetIsLeaning(true); 

	
	//SpringArmComponent->bUsePawnControlRotation = false;
	//PlayerCameraManager->ViewYawMin = -25.0f;
	//PlayerCameraManager->ViewYawMax = 25.0f;
	


}

void ADCBaseCharacter::RightLeanStop()
{
	if (bIsLeaningRight)
	{
		LeanTimeline.Reverse(); 
		bIsLeaningRight = false;
	}
	bIsLeaning = false;
	CharacterMovementComponent->SetIsLeaning(false);
}

void ADCBaseCharacter::LeftLeanStart()
{
	if (!CanLean(ELeanStatus::LeanLeft))
	{
		return;
	}

	CachedCharacterRotation = SpringArmComponent->GetForwardVector();
	LeaningAmount = (FMath::IsNegative(LeaningAmount)) ? LeaningAmount : LeaningAmount * -1.0f;
	LeaningAngle = (FMath::IsNegative(LeaningAngle)) ? LeaningAngle : LeaningAngle * -1.0f;
	LeanTimeline.Play();
	bIsLeaning = bIsLeaningLeft = true;
	CharacterMovementComponent->SetIsLeaning(true);
	

}

void ADCBaseCharacter::LeftLeanStop()
{
	if (bIsLeaningLeft)
	{
		LeanTimeline.Reverse();
		bIsLeaningLeft = false;
	}
	bIsLeaning = false;
	CharacterMovementComponent->SetIsLeaning(false);
}

void ADCBaseCharacter::ChangeFlashlightState()
{
	if (bIsFlashlightOn)
	{
		TurnOffFlashlight(); 
	}
	else
	{
		TurnOnFlashlight();
	}
}

void ADCBaseCharacter::TurnOnFlashlight()
{
	if (!IsValid(CharacterInventoryComponent) 
		|| CharacterInventoryComponent->GetItemsArray().IsEmpty() 
		|| !CharacterInventoryComponent->ContainsItem(FName("Flashlight")) 
		|| bIsFlashlightOn 
		|| !CanUseFlashlight())
	{
		return;
	}

	bIsFlashlightOn = true;
	Flashlight->SetHiddenInGame(false);
}

void ADCBaseCharacter::TurnOffFlashlight()
{
	if (CharacterInventoryComponent == nullptr 
		|| CharacterInventoryComponent->GetItemsArray().IsEmpty() 
		|| !CharacterInventoryComponent->ContainsItem(FName("Flashlight")) 
		|| !bIsFlashlightOn)
	{
		return;
	}

	bIsFlashlightOn = false; 
	Flashlight->SetHiddenInGame(true);

}

void ADCBaseCharacter::PersonalRecordsMenu()
{

}

//TODO Maybe
void ADCBaseCharacter::NextEquipment()
{
}

//TODO Maybe
void ADCBaseCharacter::PrevEquipment()
{
}

//TODO
void ADCBaseCharacter::StartFocus()
{
}

//TODO
void ADCBaseCharacter::StopFocus()
{
}

//TODO
void ADCBaseCharacter::Menu()
{
}

void ADCBaseCharacter::SetPlayerInputStatus(bool NewPlayerInput)
{
	if (NewPlayerInput)
	{
		PlayerController->EnableInput(PlayerController);
	}
	else
	{
		PlayerController->DisableInput(PlayerController);
	}
	RightLeanStop();
	LeftLeanStop(); 
}

float ADCBaseCharacter::GetAimingMovementSpeed() const
{
	return CurrentAimingMovementSpeed;
}

float ADCBaseCharacter::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

void ADCBaseCharacter::SetMouseSensitivity(float NewMouseSensitivity)
{
	MouseSensitivity = NewMouseSensitivity;
}

float ADCBaseCharacter::IsInvertCameraH() const
{
	return bIsInvertCameraH;
}

float ADCBaseCharacter::IsInvertCameraV() const
{
	return bIsInvertCameraV;
}

void ADCBaseCharacter::IsInvertCameraHor(bool bIsInvertCameraH_In)
{
	bIsInvertCameraH = bIsInvertCameraH_In;
}

void ADCBaseCharacter::IsInvertCameraVer(bool bIsInvertCameraV_In)
{
	bIsInvertCameraV = bIsInvertCameraV_In;
}

void ADCBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CrouchTimeline.TickTimeline(DeltaTime); 
	LeanTimeline.TickTimeline(DeltaTime); 
	TryChangeSprintState(DeltaTime);
	TraceLineOfSight(); 

}

void ADCBaseCharacter::UpdateCrouchTimeline(float Alpha)
{
	float TargetCameraSize = FMath::Lerp(CrouchCapsuleStartSize, CrouchCapsuleEndSize, Alpha);
	GetCapsuleComponent()->SetCapsuleHalfHeight(TargetCameraSize);
	//SpringArmComponent->SetRelativeLocation(FVector(SpringArmComponent->GetRelativeLocation().X, SpringArmComponent->GetRelativeLocation().Y, TargetCameraSize));
}

void ADCBaseCharacter::UpdateLeanTimeline(float Alpha)
{
	float TargetLocation = FMath::Lerp(0.0f, LeaningAmount, Alpha);
	float CameraRotation = FMath::Lerp(0.0f, LeaningAngle, Alpha);
	SpringArmComponent->SocketOffset = FVector(SpringArmComponent->SocketOffset.X, TargetLocation, SpringArmComponent->SocketOffset.Z); 
	PlayerController->SetControlRotation(FRotator(PlayerController->GetControlRotation().Pitch, PlayerController->GetControlRotation().Yaw, CameraRotation));
}

bool ADCBaseCharacter::CanSprint()
{
	return !(CharacterMovementComponent->IsOutOfStamina() || CharacterMovementComponent->IsCrouching() || CharacterMovementComponent->IsLeaning() || CharacterMovementComponent->MovementMode == EMovementMode::MOVE_Falling || PlayerController->IsMoveInputIgnored());
}

bool ADCBaseCharacter::CanLean(ELeanStatus LeanStatus_In)
{ 
	FVector TraceStartLocation = GetActorLocation();
	FVector TraceEndLocation;

	switch (LeanStatus_In)
	{
	case ELeanStatus::LeanRight:
		TraceEndLocation = GetActorLocation() + (GetActorRightVector() * FMath::Abs(LeaningAmount));
		break;
	case ELeanStatus::LeanLeft:
		TraceEndLocation = GetActorLocation() + (GetActorRightVector() * (FMath::IsNegative(LeaningAmount) ? LeaningAmount : -LeaningAmount));
		break;
	case ELeanStatus::None:
		TraceEndLocation = FVector::ZeroVector;
		break;
	}

	FHitResult HitResult;
	//FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, TraceEndLocation, ECC_Visibility);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, bIsHit ? TEXT("true") : TEXT("false")); 
	DrawDebugLine(GetWorld(), TraceStartLocation, TraceEndLocation, FColor::Red, true, 2.0f, 0, 2.0f);

	if (bIsHit)
	{
		return false;
	}

	return !(CharacterMovementComponent->IsLeaning() || bIsSprintRequested || LeanTimeline.IsPlaying() || LeanTimeline.IsReversing());
}

bool ADCBaseCharacter::CanUseFlashlight()
{
	return !FMath::IsNearlyZero(AttributesComponent->GetFlashlightRemainingBattery());
}

void ADCBaseCharacter::TraceLineOfSight ()
{
	if (!IsPlayerControlled())
	{
		return; 
	}

	FVector ViewLocation;
	FRotator ViewRotation; 

	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector ViewDirection = ViewRotation.Vector(); 
	FVector TraceEnd = ViewLocation + ViewDirection * LineOfSightDistance; 

	FHitResult HitResult; 
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility);
	
	if (LineOfSightObject.GetObject() != HitResult.GetActor())
	{
		LineOfSightObject = HitResult.GetActor();

		FName ActionName;
		if (LineOfSightObject.GetInterface())
		{
			HUD->SetReticleMode(true);
			ActionName = LineOfSightObject->GetActionEventName(); 
		}
		else
		{
			HUD->SetReticleMode(false);
			ActionName = NAME_None;
		}

		
	}



}

void ADCBaseCharacter::TryChangeSprintState(float DeltaTime)
{
	if (bIsSprintRequested && !CharacterMovementComponent->IsSprinting() && CanSprint())
	{
		CharacterMovementComponent->StartSprint(); 
	}
	if (CharacterMovementComponent->IsSprinting() && !(bIsSprintRequested && CanSprint()))
	{
		CharacterMovementComponent->StopSprint();
	}
}
