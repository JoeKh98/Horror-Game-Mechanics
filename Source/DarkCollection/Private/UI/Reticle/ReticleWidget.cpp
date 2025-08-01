// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Reticle/ReticleWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"

void UReticleWidget::SetReticleState(bool bIsInteracting)
{
	if (bIsInteracting)
	{
		MainReticle->SetVisibility(ESlateVisibility::Hidden); 
		InteractiveReticle->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MainReticle->SetVisibility(ESlateVisibility::Visible);
		InteractiveReticle->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UReticleWidget::NativeConstruct()
{
	FName DefaultReticleName = FName(FString::Printf(TEXT("WhiteDot")));
	MainReticle = WidgetTree->FindWidget<UImage>(DefaultReticleName);

	FName InteractReticleName = FName(FString::Printf(TEXT("InteractDot")));
	InteractiveReticle = WidgetTree->FindWidget<UImage>(InteractReticleName);

	MainReticle->SetVisibility(ESlateVisibility::Visible);
	InteractiveReticle->SetVisibility(ESlateVisibility::Hidden);
}
