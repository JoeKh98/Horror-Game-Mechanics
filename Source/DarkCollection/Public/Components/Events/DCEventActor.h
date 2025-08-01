//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "Components/TimelineComponent.h"
//#include "Curves/CurveFloat.h"
//#include "DCEventActor.generated.h"
//
//
///*
//	Enum class for storing informtion about events
//*/
//
//UENUM(BlueprintType)
//enum class EEventType : uint8
//{
//	None UMETA(DisplayName = "None"),
//	Interact UMETA(DisplayName = "On Interact"),
//	Consume UMETA(DisplayName = "On Consume"),
//	Read UMETA(DisplayName = "On Read"), 
//	LookAt UMETA(DisplayName = "On Looked At")
//};
//
//
//#pragma region EnvironmentEvents
//
//
///*
//	Struct for Actor Interactions, part of FEnvironmentEvents
//*/
//
//USTRUCT(BlueprintType)
//struct FActorsToInteract
//{
//	GENERATED_BODY()
//
//	//Add Interaction Enum
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Event")
//	TArray<class AInteractableObject*> ActorsToInteract;
//	
//	// Trigger event after N iterations
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Event", meta = (DisplayName = "After N Repeats"))
//	uint8 RepeatNum = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Event", meta = (DisplayName = "Delay Before Interaction (Sec)"))
//	float DelayBeforeInteraction = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Event", meta = (DisplayName = "Deleay Before Each Repeat (Sec)"))
//	float DelayBeforeEachRepeat = 0;
//};
//
///*
//	Sequence of transformation to 
//*/
//
//USTRUCT(BlueprintType)
//struct FTransformActorDetails
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FTransform TransformTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsSmooth = false;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float TransformDuration = 0.0f;
//};
//
///*
//	Struct to transform actors after event
//*/
//
//USTRUCT(BlueprintType)
//struct FTransformActor
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	AActor* TransformActor = nullptr;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FTransformActorDetails> TransformDetails;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction;
//};
//
//
///*
//	Struct for Actor spawn attachment details
//*/
//
//USTRUCT(BlueprintType)
//struct FSpawnActorsAttachment
//{
//	GENERATED_BODY()
//	 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	AActor* AttachToActor = nullptr; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EAttachmentRule LocationAttachmentRule = EAttachmentRule::KeepWorld; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EAttachmentRule RotationAttachmentRule = EAttachmentRule::KeepWorld; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EAttachmentRule ScaleAttachmentRule = EAttachmentRule::KeepWorld; 
//};
//
///*
//	Struct for Actor spawn
//*/
//
//USTRUCT(BlueprintType)
//struct FSpawnActors
//{
//	GENERATED_BODY()
//	 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TSubclassOf<AActor> SpawnActorClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FTransform SpawnActorTransform;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ESpawnActorCollisionHandlingMethod CollisionHandlingMethod;
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FName> SpawnedActorTags; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FSpawnActorsAttachment AttachTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction;
//
//};
//
///*
//	Struct for Hiding, Unhiding and destroying actors
//*/
//
//USTRUCT(BlueprintType)
//struct FActorsVisualOperations
//{
//	GENERATED_BODY()
//
//	//Actors that should be hidden/ unhiddent/ destroyed
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<AActor*> Actors; 
//
//	//Actors with tags that should be hidden/ unhiddent/ destroyed
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FName> GetAllActorsWithTags;
//
//	//Hide Actor? 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsHiddenInGame = false; 
//
//	//Disable collision? 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsDisableCollision = false; 
//
//	//Destroy Actor? 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsDestroyActor = false; 
//
//	//Delay before making an action
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeActions = 0.0f; 
//};
//
///*
//	Struct for dealing enviroment events
//*/
//
//USTRUCT(BlueprintType)
//struct FEnvironmentEvents
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FActorsToInteract> ActorsInteracts;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FTransformActor> TransformActors;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FSpawnActors> SpawnActors; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FActorsVisualOperations> ActorsVisualOperations; 
//};
//
///*
//	Struct that stores other structs like Environment events, Player events etc
//*/
//
//#pragma endregion
//
//#pragma region PlayerEvents
//
///*
//	--------------------------------------------LOOK AT ACTOR--------------------------------------------
//*/
//
///*
//	Struct for keeping Look at Actor event detailed settings
//*/
//USTRUCT(BlueprintType)
//struct FLookAtActorDetails
//{
//	GENERATED_BODY()
//
//	// Reference to the actor to which Player will turn
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	AActor* ActorToLookAt = nullptr; 
//	
//	// Curve for look at timeline control
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UCurveFloat* TurnToActorFloatCurve;
//
//	// How fast Player Turn to look at the other actor
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float LookAtTurnSpeed = 0.0f;
//
//	// How long Player will look at the other actor
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float LookAtDuration = 0.0f;
//};
//
///*
//	Struct Look at Actor event for letting camera to focus on some actor
//*/
//USTRUCT(BlueprintType)
//struct FLookAtActor
//{
//	GENERATED_BODY()
//
//	// Look at detailed settings
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FLookAtActorDetails> LookAtActorDetails; 
//
//	// Delay before making this
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//
//};
//
//
///*
//	--------------------------------------------DAMAGE PLAYER--------------------------------------------
//*/
//
///*
//	Struct for keeping Optional SFXs for death event
//*/
//USTRUCT(BlueprintType)
//struct FDamageSoundSettings
//{
//	GENERATED_BODY()
//
//	// Custom damage voice sound OPTIONAL
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* DamageVoiceSound = nullptr; 
//
//	// Custom death voice sound OPTIONAL
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* DeathVoiceSound = nullptr; 
//	
//	// Custom death sound OPTIONAL
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* DeathSound = nullptr; 
//};
//
//
///*
//	Struct for damaging player
//*/
//USTRUCT(BlueprintType)
//struct FDamagePlayer
//{
//	GENERATED_BODY()
//
//	// Amount of damage
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int DamageValue = 0;
//
//	// Should Player Survive after that damage
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bShouldSurvive = false;
//
//	// Has additional Damage sound
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasDamageSound = false;
//
//	// Has additional Death voice sound
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasDeathVoiceSound = false;
//
//	// Has additional Death sound
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasDeathSound = false;
//
//	// Has other HUD Damage animagtion
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasHUDDamageAnim = false;
//
//	// Has other HUD health animagtion
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasHUDHealthAnim = false;
//
//	// Has other HUD death animagtion
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasHUDDieAnim = false;
//
//	// Adding custom sounds
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FDamageSoundSettings DamageSoundSettings; 
//
//	// Delay before damage
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction; 
//};
//
//
//
///*
//	--------------------------------------------FEAR EFFECT--------------------------------------------
//*/
//
//
///*
//	Struct for dealing fear effect on player
//*/
//USTRUCT(BlueprintType)
//struct FFearPlayer
//{
//	GENERATED_BODY()
//
//	// Has fear animation
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasFearAnimation = false; 
//
//	// Has fear sound
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bHasFearSound = false;
//
//	// Optional fear sound effect
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* FearSoundEffect = nullptr;
//
//	// Delay before fear
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
//
//
///*
//	--------------------------------------------PLAYER-MASTER--------------------------------------------
//*/
//
//
///*
//	Struct for keeping all player events
//*/
//USTRUCT(BlueprintType)
//struct FPlayerEvents
//{
//	GENERATED_BODY()
//
//	// 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FLookAtActor> LookAtActor; 
//
//	// 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray <FDamagePlayer> DamagePlayer;
//
//	// 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray <FFearPlayer> FearPlayer;
//};
//
//#pragma endregion 
//
//#pragma region SoundEvents
//
///*
//	--------------------------------------------PLAY-2D-SOUND--------------------------------------------
//*/
//
///*
//	Struct for playing 2D sound
//*/
//USTRUCT(BlueprintType)
//struct FPlay2DSound
//{
//	GENERATED_BODY()
//
//	// 2D Sound to play
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* Sound = nullptr;
//
//	// Delay
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
//
//
///*
//	--------------------------------------------PLAY-3D-SOUND--------------------------------------------
//*/
//
///*
//	Struct for playing 3D sound
//*/
//USTRUCT(BlueprintType)
//struct FPlay3DSound
//{
//	GENERATED_BODY()
//
//	// 3D Sound to play
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* Sound = nullptr;
//
//	// Attach 3D Sound to actor
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	AActor* AttachToActor = nullptr;
//
//	// Actor Tag 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName ActorTag;
//	
//	// Sound Attenuation
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundAttenuation* SoundAttenuation = nullptr;
//
//	// Delay
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
//
///*
//	--------------------------------------------PLAY-AMBIENT-SOUND--------------------------------------------
//*/
//
///*
//	Struct for playing ambient sound
//*/
//USTRUCT(BlueprintType)
//struct FPlayAmbientSound
//{
//	GENERATED_BODY()
//
//	// Ambient Sound to play
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	USoundBase* Sound = nullptr;
//
//	// Ambient Sound tags
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FName> AmbientSoundTags;
//
//	// Fade in duration in seconds where 0 = instant
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float FadeInDuration = 0.0f; 
//
//	// Delay
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
//
///*
//	--------------------------------------------STOP-AMBIENT-SOUND--------------------------------------------
//*/
//
///*
//	Struct for stopping ambient sound
//*/
//USTRUCT(BlueprintType)
//struct FStopAmbientSound
//{
//	GENERATED_BODY()
//
//	// Ambient Sound tags
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FName> AmbientSoundTags;
//	
//	// Should stop all ambient sounds 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsSkipTagsAndStopAll = false;
//
//	// Fade out duration in seconds where 0 = instant
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float FadeOutDuration = 0.0f;
//
//	// Delay
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
//
///*
//	--------------------------------------------SOUND-EVENTS-MASTER--------------------------------------------
//*/
//
///*
//	Struct for storring all sound event structs
//*/
//USTRUCT(BlueprintType)
//struct FSoundEvents
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FPlay2DSound> Play2DSound;
//		
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FPlay3DSound> Play3DSound;
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FPlayAmbientSound> PlayAmbientSound;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FStopAmbientSound> StopAmbientSound;
//};
//
//#pragma endregion 
//
//#pragma region LevelEvents
//
///*
//	--------------------------------------------OPEN-LEVEL--------------------------------------------
//*/
//
///*
//	Open level details struct
//*/
//USTRUCT(BlueprintType)
//struct FOpenLevel
//{
//	GENERATED_BODY()
//
//
//	// Should open level
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bShouldOpenLevel = false;
//	
//	// Should save inventory
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bShouldKeepInventory = false;
//
//	// Level name that should be loaded
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName LevelName;
//
//	// Delay before opening a level
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f; 
//};
//
///*
//	--------------------------------------------LOAD-STREAM--------------------------------------------
//*/
//
///*
//	Unload stream details struct
//*/
//USTRUCT(BlueprintType)
//struct FLoadStream
//{
//	GENERATED_BODY()
//
//	// Level name that should be loaded
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName LevelName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bIsMakeVisibleAfterLoad = false;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bShouldBlockAfterLoad = false;
//
//	// Delay before loading a level
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
///*
//	--------------------------------------------UNLOAD-STREAM--------------------------------------------
//*/
//
///*
//	Unload stream details struct
//*/
//USTRUCT(BlueprintType)
//struct FUnloadStream
//{
//	GENERATED_BODY()
//
//	// Level name that should be unloaded
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName LevelName;
//
//	// Delay before unloading a level
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float DelayBeforeAction = 0.0f;
//};
//
///*
//	--------------------------------------------LEVEL-MASTER--------------------------------------------
//*/
//
///*
//	Main struct for keeping all other structs
//*/
//USTRUCT(BlueprintType)
//struct FLevelEvents
//{
//	GENERATED_BODY()
//
//	// Level to open
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FOpenLevel OpenLevel; 
//
//	// 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FLoadStream> LoadSteamLevels;
//
//	// 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FUnloadStream> UnloadSteamLevels; 
//
//};
//
//
//#pragma endregion 
//
//
//USTRUCT(BlueprintType)
//struct FEvents
//{
//	GENERATED_BODY()
//
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FEnvironmentEvents EnvironmentEvents;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FPlayerEvents PlayerEvents;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FSoundEvents SoundEvents;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FLevelEvents LevelEvents;
//};
//
///*
//	Struct for event all settings, the main interface layer
//*/
//
//USTRUCT(BlueprintType)
//struct FEventsManager
//{
//	GENERATED_BODY()
//
//	// Event type 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event", meta = (DisplayName = "Event Type"))
//	EEventType TriggerEventType = EEventType::None;
//
//	// Trigger event after N iterations
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event", meta = (DisplayName = "After N Times"))
//	uint8 AfterNTimes = 1; 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
//	uint8 Counter = 0; 
//
//	// Should trigger only once? 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event", meta = (DisplayName = "DoOnce"))
//	bool bDoOnce = false;
//
//	// Should Save the game? 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save", meta = (DisplayName = "Autosave"))
//	bool ShouldAutosave = false; 
//
//	// Save title
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save", meta = (DisplayName = "Save Title"))
//	FText SaveTitle;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event", meta = (DisplayName = "Add Event"))
//	FEvents Events;
//
//
//};
//
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventTriggered, FEventsManager, Event, FString, ItemID);
//
//
//
///*
//	Class for dealing with all events
//*/
//UCLASS()
//class DARKCOLLECTION_API ADCEventActor : public AActor
//{
//	GENERATED_BODY()
//
//public:	
//	// Sets default values for this component's properties
//	ADCEventActor();
//
//	UPROPERTY(BlueprintAssignable, Category = "Events")
//	FOnEventTriggered OnEventTriggered;
//
//	// Call event
//	UFUNCTION(BlueprintCallable, Category = "Events")
//	void CheckAndCreateEvents(FEvents& Event);
//
//	virtual void Tick(float DeltaTime) override;
//
//protected: 
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//private: 
//
//
//	void ExecuteDamageEvents(FEvents& Event);
//	void ExecuteDamageEvent(FDamagePlayer& DamageEvent); 
//	void ExecuteLookAtActorEvents(FEvents& Event); 
//	void ExecuteLookAtActorEvent(FLookAtActor& LookAtActorEvent);
//	void LookAtActorSequence(FLookAtActor& LookAtActorEvent);
//
//	void Delay(float Seconds, TFunction<void()> FunctionToCall);
//	void DestroyEventActor();
//
//	UFUNCTION()
//	void OnTurnToActorTimelineTick(float DeltaTime); 
//
//	UFUNCTION()
//	void OnTurnToActorTimelineFinished();
//
//	void InitializeTimeline(); 
//
//
//
//
//private: 
//	UPROPERTY()
//	class ADCBaseCharacter* Character; 
//
//	UPROPERTY()
//	FTimeline TurnToActorTimeline;
//
//
//
//
//
//	UPROPERTY()
//	FTimerHandle DelayTimerHandle;
//	
//	
//	FLookAtActor* CurrentLookAtActorEvent = nullptr;
//
//
//	FRotator CameraCurrentRotation; 
//	FRotator LookAtRotation; 
//
//	bool bHasTriggered = false; 
//	bool bIsLookAtTimelineInitialized = false; 
//	int8 LookAtCounter = 0; 
//
//	
//};
