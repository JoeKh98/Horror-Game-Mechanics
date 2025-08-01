// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DarkCollectionTypes.h"
#include "BaseDocumentationData.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UBaseDocumentationData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DocumentTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DocumentText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDocumentationType DocumentationType = EDocumentationType::None;
	
};
