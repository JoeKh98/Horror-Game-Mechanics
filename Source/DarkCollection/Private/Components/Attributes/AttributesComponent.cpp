// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Attributes/AttributesComponent.h"
#include "Character/DCBaseCharacter.h"
#include "FunctionLibraries/DCFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include <Camera/CameraComponent.h>
#include "Components/DCCharacterMovementComponent.h"


UAttributesComponent::UAttributesComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	CurrentStamina = MaxStamina; 
	CurrentFlashlightBatteryCharge = MaxFlashlightBatteryCharge; 

}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(MaxHealth > 0.0f, TEXT("void UCharacterAttributesComponent::BeginPlay() max health cannot be equal to 0"));
	checkf(GetOwner()->IsA<ADCBaseCharacter>(), TEXT("UAttributesComponent::BeginPlay() UAttributesComponent can be used only with DCBaseCharacter"));
	CachedBaseCharacter = StaticCast<ADCBaseCharacter*>(GetOwner());

	Health = MaxHealth; 

	if (GetOwner()->HasAuthority())
	{
		CachedBaseCharacter->OnTakeAnyDamage.AddDynamic(this, &UAttributesComponent::OnTakeAnyDamage);
	}

	if (FearTimelineFloat)
	{
		FOnTimelineFloat FearTimelineInterpFunc; 
		FOnTimelineEvent FearTimelineFinished; 

		FearTimelineInterpFunc.BindUFunction(this, FName("OnFearTimelineUpdate")); 
		FearTimelineFinished.BindUFunction(this, FName("OnFearTimelineFinished"));


		FearTimeline.AddInterpFloat(FearTimelineFloat, FearTimelineInterpFunc); 
		FearTimeline.SetTimelineFinishedFunc(FearTimelineFinished); 

		PlayerCamera = CachedBaseCharacter->FindComponentByClass<UCameraComponent>();
		CurrentFOV = PlayerCamera->FieldOfView; 

	}


}

bool UAttributesComponent::CanRestoreStamina()
{
	return !CachedBaseCharacter->GetCharacterMovementComponent()->IsSprinting();
}

void UAttributesComponent::OnRep_Health()
{
	OnHealthChanged();
}

void UAttributesComponent::OnHealthChanged()
{
	if (OnHealthChangedEvent.IsBound())
	{
		OnHealthChangedEvent.Broadcast(GetHealth());
	}

	if (Health <= 0)
	{
		if (OnDeathEvent.IsBound())
		{
			OnDeathEvent.Broadcast(); 
		}
	}
}

void UAttributesComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsAlive())
	{
		return; 
	}

	UE_LOG(LogDamage, Warning, TEXT("UAttributesComponent::OnTakeAnyDamage %s recieved %.2f amount of damage from %s"), *CachedBaseCharacter->GetName(), Damage, *DamageCauser->GetName());

	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);

	OnHealthChanged();

}

void UAttributesComponent::OnFearTimelineUpdate(float Value)
{
	// Opacity of fear widget

	float NewFOV = FMath::Lerp(CurrentFOV, CurrentFOV + 5.0f, Value); 
	PlayerCamera->SetFieldOfView(NewFOV);
}

void UAttributesComponent::OnFearTimelineFinished()
{
}

void UAttributesComponent::UpdateStamina(float DeltaTime)
{
	if (FMath::IsNearlyZero(CurrentStamina))
	{
		CachedBaseCharacter->GetCharacterMovementComponent()->SetIsOutOfStamina(true);
	}
	if (CachedBaseCharacter->GetCharacterMovementComponent()->IsSprinting())
	{
		CurrentStamina -= StaminaSprintConsumption * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
	}
	if (CanRestoreStamina())
	{
		CurrentStamina += StaminaRestoreSpeed * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina); 
	}
	if (FMath::IsNearlyEqual(CurrentStamina, MaxStamina))
	{
		CachedBaseCharacter->GetCharacterMovementComponent()->SetIsOutOfStamina(false); 
	}

}

void UAttributesComponent::UpdateFlashlightBattery(float DeltaTime)
{

	if (FMath::IsNearlyZero(CurrentFlashlightBatteryCharge))
	{
		CachedBaseCharacter->ChangeFlashlightState();
	}

	if (CachedBaseCharacter->IsFlashlightOn())
	{
		CurrentFlashlightBatteryCharge -= FlashlightBatteryChargeConsumption * DeltaTime;
		CurrentFlashlightBatteryCharge = FMath::Clamp(CurrentFlashlightBatteryCharge, 0.0f, MaxFlashlightBatteryCharge);
	}



}

void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStamina(DeltaTime); 
	UpdateFlashlightBattery(DeltaTime); 
	FearTimeline.TickTimeline(DeltaTime); 

}

bool UAttributesComponent::IsAlive()
{
	return Health > 0;
}

void UAttributesComponent::AddHealth(uint8 HealthToAdd)
{
	Health = FMath::Clamp(Health + HealthToAdd, 0, MaxHealth); 
	OnHealthChanged(); 
}

void UAttributesComponent::ApplyDamage(uint8 DamageAmount, AActor* DamageInstigator)
{
	if (!IsAlive())
	{
		return;
	}

	UE_LOG(LogDamage, Warning, TEXT("UAttributesComponent::OnTakeAnyDamage %s recieved %.2f amount of damage from %s"), *CachedBaseCharacter->GetName(), DamageAmount, *DamageInstigator->GetName());

	Health = FMath::Clamp(Health - DamageAmount, 0, MaxHealth);

	OnHealthChanged();
}

uint8 UAttributesComponent::GetHealth() const
{
	return Health;
}

void UAttributesComponent::SetHealth(uint8 NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth); 
}

uint8 UAttributesComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UAttributesComponent::RestoreFullStamina()
{
	CurrentStamina = MaxStamina; 
}

float UAttributesComponent::GetCurrentStamina() const
{
	return CurrentStamina;
}

void UAttributesComponent::RestoreFlashlightBattery()
{
	CurrentFlashlightBatteryCharge = MaxFlashlightBatteryCharge; 
}

float UAttributesComponent::GetFlashlightRemainingBattery() const
{
	return CurrentFlashlightBatteryCharge;
}

void UAttributesComponent::SetFlashlightRemainingBattery(float NewFlashlightRemainingBattery)
{
	CurrentFlashlightBatteryCharge = FMath::Clamp(NewFlashlightRemainingBattery, 0.0f, MaxFlashlightBatteryCharge); 
}

void UAttributesComponent::RechargeFlashlight()
{
	CurrentFlashlightBatteryCharge = MaxFlashlightBatteryCharge; 
}

void UAttributesComponent::Fear(FFearPlayer FearEvent)
{
	if (!IsAlive())
	{
		return;
	}

	if (FearEvent.bHasFearSound)
	{
		if (IsValid(FearEvent.FearSoundEffect))
		{
			if (CurrentFearSound)
			{
				CurrentFearSound->Stop(); 
			}
			CurrentFearSound = UDCFunctionLibrary::Play2DSound(GetWorld(), FearEvent.FearSoundEffect);
			
		}
	
	}
	else
	{
		// Play standard fear SFX
	}

	if (FearEvent.bHasFearAnimation)
	{
		FearTimeline.PlayFromStart(); 
	}



}




