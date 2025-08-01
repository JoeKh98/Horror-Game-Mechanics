// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveSystem/DCSaveGame.h"
#include "DCBaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DARKCOLLECTION_API UDCBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 

	UDCBaseGameInstance();

	UFUNCTION(BlueprintPure)
	FString GetSaveSlotName() const; 

	UFUNCTION(BlueprintPure)
	class UDCSaveComponent* GetSaveComponent() const; 

	UFUNCTION(BlueprintCallable)
	void SetSaveSlotName(FString NewSaveSlotName); 

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FString SaveSlotName;

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory and Docs")
	FInventorySaveInfo InventoryAndDocsCache; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory and Docs")
	bool bIsNewLevel = true; 

private:

	UPROPERTY()
	class UDCSaveComponent* SaveComponent; 

};
