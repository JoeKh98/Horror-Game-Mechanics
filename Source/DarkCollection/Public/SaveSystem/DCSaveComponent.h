#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveSystem/DCSaveGame.h"
#include "DCSaveComponent.generated.h"



class ADCBaseCharacter; 
class UDCSaveGame;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKCOLLECTION_API UDCSaveComponent : public UActorComponent
{
	GENERATED_BODY()



public:	
	
	UDCSaveComponent();
	void CollectStreaming(FName LevelName, bool bIsStreaming);

private: 


	void CaptureThubnail(ADCBaseCharacter* Player); 
	void SetSlotName();
	void SaveAllEquipables();
	void SavePlayer(); 
	void SaveEvents();
	void SaveCollectUsables(); 
	void SaveAmbientSounds(); 
	void SaveVariables(); 

	void LoadPlayer(ADCBaseCharacter* PlayerCharacter, UDCSaveGame* LoadSlot);
	void LoadAllEquipables(UDCSaveGame* LoadSlot);
	void LoadStreaming(UDCSaveGame* LoadSlot);
	void OnLevelLoaded(UDCSaveGame* LoadSlot);

protected:
	
	virtual void BeginPlay() override;

	


public:	
	
	UFUNCTION(BlueprintCallable)
	void CreateSaveGame(); 

	UFUNCTION(BlueprintCallable)
	void SaveGame(FText NewTitle);
	//void SaveInventory(FText Title);

	UFUNCTION(BlueprintCallable)
	void LoadGame(FString SlotName_In);

	UFUNCTION(BlueprintCallable)
	void LoadLastSave(); 

	

		

public:  

	UPROPERTY(BlueprintReadOnly)
	UDCSaveGame* SaveGameRef;
	
	UPROPERTY()
	FText Title; 

	UPROPERTY()
	FString SlotName = "HanselAndGretel";

	UPROPERTY()
	FString SettingsSlotName = "Settings";	
	

	UPROPERTY()
	bool bIsAutoSave = true; 

private:

	UPROPERTY()
	TArray<FLevelSaveInfo> StreamingCache; 

	UPROPERTY()
	ADCBaseCharacter* PlayerCharacter; 

	int8 StreamingCacheIndex = 0;

};
