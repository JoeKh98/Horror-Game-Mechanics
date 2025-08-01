// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/DCEventManager.h"

UDCEventManager* UDCEventManager::GetInstance(UWorld* World)
{
    static UDCEventManager* Instance = NewObject<UDCEventManager>(); 
    return Instance; 
}

void UDCEventManager::RegisterEvent(const FString& EventID, TFunction<void()> Callback)
{
    Events.FindOrAdd(EventID).Add(Callback); 
}

void UDCEventManager::TriggerEvent(const FString& EventID)
{
    if (Events.Contains(EventID))
    {
        for (const auto& Callback : Events[EventID])
        {
            Callback(); 
        }
    }
}

