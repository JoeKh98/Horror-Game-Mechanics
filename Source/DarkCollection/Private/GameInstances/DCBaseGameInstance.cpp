// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/DCBaseGameInstance.h"
#include "SaveSystem/DCSaveComponent.h"

UDCBaseGameInstance::UDCBaseGameInstance()
{
	SaveComponent = CreateDefaultSubobject<UDCSaveComponent>(FName("SaveComponent")); 
	SaveComponent->CreateSaveGame(); 

}

FString UDCBaseGameInstance::GetSaveSlotName() const
{
	return SaveSlotName;
}

UDCSaveComponent* UDCBaseGameInstance::GetSaveComponent() const
{
	return SaveComponent;
}

void UDCBaseGameInstance::SetSaveSlotName(FString NewSaveSlotName)
{
	SaveSlotName = NewSaveSlotName; 
}
