// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReticleWidget.generated.h"


class UImage; 

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UReticleWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	
	void SetReticleState(bool bIsInteracting); 

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	UImage* MainReticle; 

	UPROPERTY(BlueprintReadWrite)
	UImage* InteractiveReticle;

private:


};
