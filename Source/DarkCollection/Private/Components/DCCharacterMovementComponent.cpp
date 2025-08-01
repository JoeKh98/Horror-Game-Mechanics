// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DCCharacterMovementComponent.h"
#include "Character/DCBaseCharacter.h"
#include "Components/Attributes/AttributesComponent.h"



bool UDCCharacterMovementComponent::IsOutOfStamina() const
{
    return bIsOutOfStamina;
}


void UDCCharacterMovementComponent::SetIsOutOfStamina(bool bIsOutOfStamina_In)
{
    bIsOutOfStamina = bIsOutOfStamina_In;
}

void UDCCharacterMovementComponent::StartSprint()
{
    bIsSprinting = true;
    bForceMaxAccel = 1;
}

void UDCCharacterMovementComponent::StopSprint()
{
	bIsSprinting = false;
	bForceMaxAccel = 0;
    
}

float UDCCharacterMovementComponent::GetMaxSpeed() const
{
    float Result = Super::GetMaxSpeed();
    if (bIsSprinting)
    {
        Result = SprintSpeed;
    }
    else if (bIsOutOfStamina)
    {
        Result = 200.0f;
    }
    else if (GetBaseCharacterOwner()->IsAiming())
    {
        Result = GetBaseCharacterOwner()->GetAimingMovementSpeed();
    }
    else if (GetBaseCharacterOwner()->IsLeaning())
    {
        Result = LeaningSpeed; 
    }
    //else if (IsOnLadder())
    //{
    //    Result = ClimbingOnLadderMaxSpeed;
    //}


    return Result;
}

ADCBaseCharacter* UDCCharacterMovementComponent::GetBaseCharacterOwner() const
{
    return StaticCast<ADCBaseCharacter*>(CharacterOwner);
}
