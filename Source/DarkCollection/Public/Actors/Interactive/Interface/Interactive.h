// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"


class ADCBaseCharacter; 

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKCOLLECTION_API IInteractable
{

	GENERATED_BODY()

public:

	virtual void Interact(ADCBaseCharacter* Character) PURE_VIRTUAL(IInteractable::Interact,);
	virtual FName GetActionEventName() const PURE_VIRTUAL(IInteractable::GetActionEventName(), return FName(NAME_None); );
};
