// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/DCFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

FString UDCFunctionLibrary::GetImgDate()
{
	FDateTime Time = UKismetMathLibrary::Now(); 
	FString Result = FString::FromInt(Time.GetYear()); 

	// Month
	Result += FString::FromInt(Time.GetMonth()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetMonth())) : (FString::FromInt(Time.GetMonth()));
	
	// Day
	Result += FString::FromInt(Time.GetDay()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetDay())) : (FString::FromInt(Time.GetDay()));

	// Space
	Result += "_"; 

	// Hour
	Result += FString::FromInt(Time.GetHour()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetHour())) : (FString::FromInt(Time.GetHour()));

	// Minute 
	Result += FString::FromInt(Time.GetMinute()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetMinute())) : (FString::FromInt(Time.GetMinute()));

	// Second 
	Result += FString::FromInt(Time.GetSecond()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetSecond())) : (FString::FromInt(Time.GetSecond()));

	return Result;
}

FString UDCFunctionLibrary::GetDate()
{
	FDateTime Time = UKismetMathLibrary::Now();

	// Day
	FString Result = FString::FromInt(Time.GetDay()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetDay())) : (FString::FromInt(Time.GetDay()));
	// Space
	Result += "/"; 
	// Month
	Result += FString::FromInt(Time.GetMonth()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetMonth())) : (FString::FromInt(Time.GetMonth()));
	// Space
	Result += "/";
	// Year
	Result += FString::FromInt(Time.GetYear()); 

	// Space
	Result += "  ";

	// Hour
	Result += FString::FromInt(Time.GetHour()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetHour())) : (FString::FromInt(Time.GetHour()));

	// Minute 
	Result += FString::FromInt(Time.GetMinute()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetMinute())) : (FString::FromInt(Time.GetMinute()));

	// Second 
	Result += FString::FromInt(Time.GetSecond()).Len() - 1 == 0 ? ("0" + FString::FromInt(Time.GetSecond())) : (FString::FromInt(Time.GetSecond()));

	return Result;
}

UAudioComponent* UDCFunctionLibrary::Play2DSound(UObject* WorldContextObject, USoundBase* Sound, bool bIsStopExisting)
{
	UAudioComponent* AudioComponent = nullptr; 

	if (Sound)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(WorldContextObject, Sound);
	}

	return AudioComponent;
}
