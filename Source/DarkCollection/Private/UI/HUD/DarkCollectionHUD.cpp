// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DarkCollectionHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/Reticle/ReticleWidget.h"
//#include "Blueprint/UserWidget.h"

//void ADarkCollectionHUD::SetReticleMode(bool bIsInteracting)
//{
//	if (bIsInteracting)
//	{
//		MainReticle->RemoveFromViewport(); 
//		InteractReticle->AddToViewport(0); 
//	}
//
//}

void ADarkCollectionHUD::SetReticleMode(bool bIsInteracting)
{
	if (!IsValid(ReticleWidget))
	{
		return; 
	}

	ReticleWidget->SetReticleState(bIsInteracting);
}

void ADarkCollectionHUD::BeginPlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerController, ReticleWidgetClass);
	if (IsValid(NewWidget))
	{
		NewWidget->AddToViewport(0);
	}
	
	ReticleWidget = StaticCast<UReticleWidget*>(NewWidget);


}
