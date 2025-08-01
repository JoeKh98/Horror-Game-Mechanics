// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem/DCSaveComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "SaveSystem/DCSaveGame.h"
#include "FunctionLibraries/DCFunctionLibrary.h"
#include "Character/DCBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Attributes/AttributesComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include"Actors/Interactive/Equipable/EquipableItem.h"
#include"Actors/Interactive/Equipable/EquipableDocumentation.h"
#include "GameInstances/DCBaseGameInstance.h"
//#include "Kismet/KismetRenderingLibrary.h"
//#include "Components/SceneCaptureComponent2D.h"
//#include "ImageWriteQueue/Public/ImageWriteBlueprintLibrary.h"
//#include "GameInstances/DCBaseGameInstance.h"
//#include "Kismet/KismetMathLibrary.h"



UDCSaveComponent::UDCSaveComponent()
{ 
}

void UDCSaveComponent::CaptureThubnail(ADCBaseCharacter* Player)
{
	FString ThubnailName;


	//USceneCaptureComponent2D* ThumbnailCapture; 

	ThubnailName = UKismetSystemLibrary::GetProjectSavedDirectory() + FString("\\SaveGames\\thumbs\\") + UDCFunctionLibrary::GetImgDate() + FString("_thumb.jpg");
	SaveGameRef->Thubnail = ThubnailName; 
	//ThumbnailCapture->TextureTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, 128, 128, ETextureRenderTargetFormat::RTF_RGBA8_SRGB, FLinearColor::Black, true);
	//ThumbnailCapture->bCaptureEveryFrame = true; 
	
	//TODO
	
}

void UDCSaveComponent::SetSlotName()
{
	//if (SaveGameRef->SaveSlotList.IsEmpty())
	//{
	//	SlotName = FString("Slot1");
	//}
	//else
	//{
	//	SlotName = FString("Slot1") + FString::FromInt(SaveGameRef->SaveSlotList.Num());
	//}

	SlotName = "HanselAndGretel";
}

void UDCSaveComponent::SaveAllEquipables()
{
	TArray<AActor*> EquipableItems; 
	TArray<AActor*> EquipableDocs; 
	UGameplayStatics::GetAllActorsOfClass(PlayerCharacter, AEquipableItem::StaticClass(), EquipableItems);
	UGameplayStatics::GetAllActorsOfClass(PlayerCharacter, AEquipableDocumentation::StaticClass(), EquipableDocs);

	if (EquipableItems.IsEmpty() || !IsValid(SaveGameRef))
	{
		return; 
	}

	// Save Items
	for (const AActor* CurrentItem : EquipableItems)
	{
		if (IsValid(CurrentItem))
		{
			FLevelEquipablesSaveInfo ItemInfo; 
			ItemInfo.ItemClass = CurrentItem->GetClass(); 
			ItemInfo.ItemTransform = FTransform(CurrentItem->GetActorRotation(), CurrentItem->GetActorLocation(), CurrentItem->GetActorScale());
			SaveGameRef->LevelEquipablesSave.Add(ItemInfo); 
		}
	}
}

void UDCSaveComponent::SavePlayer()
{
	if (!IsValid(PlayerCharacter))
	{
		return; 
	}

	FPlayerSaveInfo& Player = SaveGameRef->PlayerSave; 

	FTransform PlayerTransform; 
	PlayerTransform.SetLocation(PlayerCharacter->GetCapsuleComponent()->GetComponentLocation());
	PlayerTransform.SetRotation(PlayerCharacter->GetController()->GetControlRotation().Quaternion());
	PlayerTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f)); 

	// Player Saves
	Player.PlayerTransform = PlayerTransform; 
	Player.Health = PlayerCharacter->GetCharacterAttributesComponent()->GetHealth(); 
	Player.FlashlightRemainingBattery = PlayerCharacter->GetCharacterAttributesComponent()->GetFlashlightRemainingBattery();
	Player.HasFlashlight = PlayerCharacter->GetCharacterInventoryComponent()->ContainsItem(FName("Flashlight"));
	Player.IsFlashlightOn = PlayerCharacter->IsFlashlightOn();
	Player.IsCrouching = PlayerCharacter->bIsCrouched;
	Player.IsStuck = false;

	// Inventory
	Player.InventorySave.ItemArray = PlayerCharacter->GetCharacterInventoryComponent()->GetItemsArray(); 
	Player.InventorySave.DocumentationArray = PlayerCharacter->GetCharacterInventoryComponent()->GetDocumentationArray(); 

	SaveGameRef->PlayerSave = Player;
}

void UDCSaveComponent::SaveEvents()
{
}

void UDCSaveComponent::SaveCollectUsables()
{
}

void UDCSaveComponent::SaveAmbientSounds()
{
}

void UDCSaveComponent::SaveVariables()
{
	SaveGameRef->LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	SaveGameRef->Date = UDCFunctionLibrary::GetDate(); 
	SaveGameRef->Title = FText::FromString(SlotName); 
	SaveGameRef->StreamingCache = StreamingCache; 
	
	UGameplayStatics::SaveGameToSlot(SaveGameRef, SlotName, 0); 

}

void UDCSaveComponent::CollectStreaming(FName LevelName, bool bIsStreaming)
{

	if (!StreamingCache.Contains(FLevelSaveInfo(LevelName, bIsStreaming)))
	{
		if (StreamingCache.Contains(FLevelSaveInfo(LevelName, !bIsStreaming)))
		{
			if (StreamingCache.Contains(FLevelSaveInfo(LevelName, !bIsStreaming)))
			{
				StreamingCache[StreamingCache.Find(FLevelSaveInfo(LevelName, !bIsStreaming))] = FLevelSaveInfo(LevelName, bIsStreaming);
			}

		}
		else
		{
			StreamingCache.Add(FLevelSaveInfo(LevelName, bIsStreaming)); 
		}
	}
}

void UDCSaveComponent::LoadPlayer(ADCBaseCharacter* Player, UDCSaveGame* LoadSlot)
{
	// Load Player Location and Rotation
	FTransform PlayerTransformTest = LoadSlot->PlayerSave.PlayerTransform;
	Player->SetActorLocationAndRotation(PlayerTransformTest.GetLocation(), PlayerTransformTest.GetRotation(), false, nullptr, ETeleportType::ResetPhysics);
	Player->GetController()->SetControlRotation(PlayerTransformTest.GetRotation().Rotator());
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Game Loaded"));

	// Load Player Health
	Player->GetCharacterAttributesComponent()->SetHealth(LoadSlot->PlayerSave.Health);

	// Load Flashlight Remaining Battery
	Player->GetCharacterAttributesComponent()->SetFlashlightRemainingBattery(LoadSlot->PlayerSave.FlashlightRemainingBattery);

	// Load Has Flashlight
	// LoadSlot->PlayerSave.HasFlashlight = PlayerCharacter->GetCharacterInventoryComponent()->ContainsItem(TEXT("Flashlight")); 

	// Load Was Flashlight On
	if (LoadSlot->PlayerSave.IsFlashlightOn) { Player->TurnOnFlashlight(); }

	// Load Is Crouching 
	if (LoadSlot->PlayerSave.IsCrouching && !PlayerCharacter->bIsCrouched) { PlayerCharacter->ChangeCrouchState(); }

	// Load Inventory Items and Docs 
	PlayerCharacter->GetCharacterInventoryComponent()->SetItemsArray(LoadSlot->PlayerSave.InventorySave.ItemArray);
	PlayerCharacter->GetCharacterInventoryComponent()->SetDocumentationArray(LoadSlot->PlayerSave.InventorySave.DocumentationArray); 
}

void UDCSaveComponent::LoadAllEquipables(UDCSaveGame* LoadSlot)
{
	if (IsValid(LoadSlot))
	{
		FActorSpawnParameters SpawnParameters; 
		
		for (FLevelEquipablesSaveInfo CurrentItem : LoadSlot->LevelEquipablesSave)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = nullptr;          // Optional owner of the actor
			SpawnParams.Instigator = nullptr;     // Optional instigator (used for damage tracing, etc.)
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			
			// Spawn the actor
			PlayerCharacter->GetWorld()->SpawnActor<AEquipableItem>(CurrentItem.ItemClass, CurrentItem.ItemTransform, SpawnParams);
		}
		
	}
}

void UDCSaveComponent::LoadStreaming(UDCSaveGame* LoadSlot)
{
	if (StreamingCache.IsValidIndex(0))
	{

		FLevelSaveInfo LevelSaveInfo =  StreamingCache[StreamingCacheIndex];
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = 1234; // ”никальный ID
		LatentInfo.Linkage = 0;
		LatentInfo.ExecutionFunction = "OnLevelLoaded";

		if (LevelSaveInfo.IsStreaming)
		{
			UGameplayStatics::LoadStreamLevel(GetWorld(), LevelSaveInfo.LevelName, true, true, LatentInfo);
		}
		else
		{
			UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelSaveInfo.LevelName, LatentInfo, true);
		}
	}
}

void UDCSaveComponent::OnLevelLoaded(UDCSaveGame* LoadSlot)
{
	if (StreamingCache.Num() - 1 == StreamingCacheIndex)
	{
		StreamingCacheIndex = 0;
	}
	else
	{
		StreamingCacheIndex++;
		LoadStreaming(LoadSlot);
	}
}

void UDCSaveComponent::BeginPlay()
{
	
}

void UDCSaveComponent::CreateSaveGame()
{
	SaveGameRef = Cast<UDCSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (IsValid(SaveGameRef))
	{
		UE_LOG(LogTemp, Log, TEXT("Game loaded successfully!"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game loaded successfully!"), true, FVector2D(4.0f, 4.0f));
	}
	else
	{
		SaveGameRef = Cast<UDCSaveGame>(UGameplayStatics::CreateSaveGameObject(UDCSaveGame::StaticClass()));
		if (!SaveGameRef)
		{
			UE_LOG(LogTemp, Log, TEXT("Failed to create slot!"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to create slot!"), true, FVector2D(4.0f, 4.0f));
			return; 
		}
	}
}

void UDCSaveComponent::SaveGame(FText NewTitle)
{
	PlayerCharacter = Cast<ADCBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetOuter()->GetWorld(), 0));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Game Saved"));
	SaveGameRef->Title = FText::FromString(SlotName); // Should be title
	CaptureThubnail(PlayerCharacter); 
	SetSlotName(); 
	SavePlayer(); 
	SaveAllEquipables(); 
	SaveVariables(); 

}

void UDCSaveComponent::LoadGame(FString SlotName_In)
{
	PlayerCharacter = Cast<ADCBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetOuter()->GetWorld(), 0));
	UDCBaseGameInstance* GameInstance = Cast<UDCBaseGameInstance>(GetOuter());
	
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is not Valid!")); 
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("GameInstance is not Valid!"));
		return;
	}

	GameInstance->SetSaveSlotName(SlotName); // Always load 1 slot
	
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0)) // Same here
	{
		UDCSaveGame* LoadSlot = Cast<UDCSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->GetSaveSlotName(), 0));
		if (IsValid(LoadSlot) && IsValid(PlayerCharacter))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Load Slot is not Valid"));

			//UGameplayStatics::OpenLevel(GetWorld(), *LoadSlot->LevelName, true);

			// Load Player, Inventory and Documentations 
			LoadPlayer(PlayerCharacter, LoadSlot);

			// Load Level Equipables
			LoadAllEquipables(LoadSlot);

			// Load Level streaming info 
			LoadStreaming(LoadSlot); 



		}

		



	}
	
}

void UDCSaveComponent::LoadLastSave()
{

}

