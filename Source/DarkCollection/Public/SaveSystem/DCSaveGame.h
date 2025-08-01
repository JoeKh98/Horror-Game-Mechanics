// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/Structs/InventoryItemSlotData.h"

#include "GameFramework/GameUserSettings.h"
#include "DCSaveGame.generated.h"


UENUM(BlueprintType)
enum class EFPSLimit : uint8
{
	FPS_30 UMETA(DisplayName = "30"),
	FPS_60 UMETA(DisplayName = "60"),
	FPS_120 UMETA(DisplayName = "120"),
	FPS_144 UMETA(DisplayName = "144"),
	FPS_240 UMETA(DisplayName = "240"),
	FPS_600 UMETA(DisplayName = "600")
};


USTRUCT(BlueprintType)
struct FInventorySaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UBaseDocumentationData*> DocumentationArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItemSlotData> ItemArray;
};

USTRUCT(BlueprintType)
struct FPlayerSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlayerTransform;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FlashlightRemainingBattery; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasFlashlight; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFlashlightOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCrouching; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStuck; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySaveInfo InventorySave; 

};

USTRUCT(BlueprintType)
struct FGameplaySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOV = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DepthOfField = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MasterVolume = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectsVolume = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	float DialogueVolume = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolume = 100.0f;

};

USTRUCT(BlueprintType)
struct FPlayerInputSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InvertCameraV = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InvertCameraH = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraSensivity = 0.5f; 

};

USTRUCT(BlueprintType)
struct FGraphicSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Resolution = FIntPoint(1920, 1080);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> ScreenMode = EWindowMode::WindowedFullscreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool VSync = false;


	/////////////////////////////////////////////////// QUALITY ///////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFPSLimit FPSLimit = EFPSLimit::FPS_600; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ViewDistance = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 AntiAliasing = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	uint8 PostProcessing = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Shadows = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Texture = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 VisualEffects = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Foliage = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Shading = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 GlobalIlluminationMethod = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 GlobalIllumination = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ReflectionMethod = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ReflectionQuality = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 VolumetricFog = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ScreenPercentage = 100;

};

USTRUCT(BlueprintType)
struct FLevelSaveInfo
{
	GENERATED_BODY()
	FLevelSaveInfo() {};
	FLevelSaveInfo(FName LevelName_In, bool bIsStreaming_In) : LevelName(LevelName_In), IsStreaming(bIsStreaming_In) {}
	bool operator==(const FLevelSaveInfo& Other) const
	{
		return LevelName == Other.LevelName && IsStreaming == Other.IsStreaming;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStreaming;

};

USTRUCT(BlueprintType)
struct FLevelEquipablesSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ItemTransform; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEquipableItem> ItemClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//uint8 NumberToAddInventory; 

};

USTRUCT(BlueprintType)
struct FAmbientSoundsSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AmbientSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Tags; 

};

USTRUCT(BlueprintType)
struct FAssetSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BoolSlot01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BoolSlot02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BoolSlot03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BoolSlot04;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FloatSlot01; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FloatSlot02; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IntSlot01; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan TimespanSlot; 
};


UCLASS()
class DARKCOLLECTION_API UDCSaveGame : public USaveGame
{
	GENERATED_BODY()

	

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	TArray<FLevelEquipablesSaveInfo> LevelEquipablesSave; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FPlayerSaveInfo PlayerSave; 

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	//FInventorySaveInfo InventorySave; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	TArray<FString> Delete; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	TArray<FAssetSaveInfo> AssetsSave; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FAmbientSoundsSaveInfo AmbientSoundInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FLevelSaveInfo LevelSave;
	
	//Event save
	//Auto save

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FString Date; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	TArray<uint8> SaveSlotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FString Thubnail; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FGameplaySettings GameplaySettingsSave; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FGraphicSettings GraphicSettingsSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	FPlayerInputSettings InputSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	TArray<FLevelSaveInfo> StreamingCache;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save System")
	bool Autosave; 


};
