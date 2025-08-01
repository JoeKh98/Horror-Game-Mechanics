#include "Character/Controller/DCBasePlayerController.h"
#include "Character/DCBaseCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/HUD/DarkCollectionHUD.h"
#include "DarkCollectionTypes.h"

// Constructor
ADCBasePlayerController::ADCBasePlayerController()
{
	// Nothing special in the constructor yet
}

// Called when the Pawn is assigned to the controller
void ADCBasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Cache a reference to the controlled character
	CachedBaseCharacter = Cast<ADCBaseCharacter>(InPawn);

	if (CachedBaseCharacter.IsValid() && IsLocalController())
	{
		// Future logic for when pawn is set locally
	}
}

// Called when the game starts or when spawned
void ADCBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the controller possesses a pawn
void ADCBasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

// Set up input bindings for player control
void ADCBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Axis bindings
	InputComponent->BindAxis("MoveForward", this, &ADCBasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADCBasePlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ADCBasePlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &ADCBasePlayerController::Turn);

	// Action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADCBasePlayerController::Jump);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ADCBasePlayerController::ChangeCrouchState);
	InputComponent->BindAction(ActionInteract, IE_Pressed, this, &ADCBasePlayerController::Interact);
	InputComponent->BindAction("Run", IE_Pressed, this, &ADCBasePlayerController::StartSprint);
	InputComponent->BindAction("Run", IE_Released, this, &ADCBasePlayerController::StopSprint);
	InputComponent->BindAction("LeanRight", IE_Pressed, this, &ADCBasePlayerController::RightLeanStart);
	InputComponent->BindAction("LeanRight", IE_Released, this, &ADCBasePlayerController::RightLeanStop);
	InputComponent->BindAction("LeanLeft", IE_Pressed, this, &ADCBasePlayerController::LeftLeanStart);
	InputComponent->BindAction("LeanLeft", IE_Released, this, &ADCBasePlayerController::LeftLeanStop);
	InputComponent->BindAction("Flashlight", IE_Pressed, this, &ADCBasePlayerController::ChangeFlashlightState);
	InputComponent->BindAction("NextEquipment", IE_Pressed, this, &ADCBasePlayerController::NextEquipment);
	InputComponent->BindAction("PrevEquipment", IE_Pressed, this, &ADCBasePlayerController::PrevEquipment);
	InputComponent->BindAction("Focus", IE_Pressed, this, &ADCBasePlayerController::StartFocus);
	InputComponent->BindAction("Focus", IE_Released, this, &ADCBasePlayerController::StopFocus);
	InputComponent->BindAction("Menu", IE_Pressed, this, &ADCBasePlayerController::Menu);

	// Allow menu actions even when game is paused
	FInputActionBinding& ToggleMenuBinding = InputComponent->BindAction("PersonalRecordsMenu", IE_Pressed, this, &ADCBasePlayerController::PersonalRecordsMenu);
	ToggleMenuBinding.bExecuteWhenPaused = true;

	FInputActionBinding& ToggleInventoryBinding = InputComponent->BindAction("Inventory", IE_Pressed, this, &ADCBasePlayerController::Inventory);
	ToggleInventoryBinding.bExecuteWhenPaused = true;
}

// Movement/Input handlers
void ADCBasePlayerController::MoveForward(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void ADCBasePlayerController::MoveRight(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void ADCBasePlayerController::Turn(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Turn(Value);
	}
}

void ADCBasePlayerController::LookUp(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUp(Value);
	}
}

void ADCBasePlayerController::Jump()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void ADCBasePlayerController::ChangeCrouchState()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->ChangeCrouchState();
	}
}

void ADCBasePlayerController::Interact()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Interact();
	}
}

void ADCBasePlayerController::StartSprint()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartSprint();
	}
}

void ADCBasePlayerController::StopSprint()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopSprint();
	}
}

void ADCBasePlayerController::RightLeanStart()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->RightLeanStart();
	}
}

void ADCBasePlayerController::RightLeanStop()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->RightLeanStop();
	}
}

void ADCBasePlayerController::LeftLeanStart()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LeftLeanStart();
	}
}

void ADCBasePlayerController::LeftLeanStop()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LeftLeanStop();
	}
}

void ADCBasePlayerController::ChangeFlashlightState()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->ChangeFlashlightState();
	}
}

void ADCBasePlayerController::NextEquipment()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->NextEquipment();
	}
}

void ADCBasePlayerController::PrevEquipment()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->PrevEquipment();
	}
}

void ADCBasePlayerController::StartFocus()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartFocus();
	}
}

void ADCBasePlayerController::StopFocus()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopFocus();
	}
}

void ADCBasePlayerController::Menu()
{
	// Placeholder for game menu logic
}

// Toggle the Personal Records Menu
void ADCBasePlayerController::PersonalRecordsMenu()
{
	if (IsValid(PersonalRecordsMenuWidget) && PersonalRecordsMenuWidget->IsVisible())
	{
		IsInPersonalRecordsMenu = false;
		PersonalRecordsMenuWidget->RemoveFromParent();
		PersonalRecordsMenuWidget = nullptr;
		SetInputMode(FInputModeGameOnly{});
		SetPause(false);
		bShowMouseCursor = false;
	}
	else
	{
		IsInPersonalRecordsMenu = true;
		if (!IsValid(PersonalRecordsMenuWidget))
		{
			PersonalRecordsMenuWidget = CreateWidget<UUserWidget>(
				this,
				Cast<ADarkCollectionHUD>(GetHUD())->PersonalRecordsMenuWidgetClass);
		}
		PersonalRecordsMenuWidget->AddToViewport(1);
		SetInputMode(FInputModeGameAndUI{});
		SetPause(true);
		bShowMouseCursor = true;
	}
}

// Toggle the Inventory Menu
void ADCBasePlayerController::Inventory()
{
	if (IsValid(InventoryWidget) && InventoryWidget->IsVisible())
	{
		IsInInventory = false;
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;
		SetInputMode(FInputModeGameOnly{});
		SetPause(false);
		bShowMouseCursor = false;
	}
	else
	{
		IsInInventory = true;
		if (!IsValid(InventoryWidget))
		{
			InventoryWidget = CreateWidget<UUserWidget>(
				this,
				Cast<ADarkCollectionHUD>(GetHUD())->InventoryWidgetClass);
		}
		InventoryWidget->AddToViewport(1);
		SetInputMode(FInputModeGameAndUI{});
		SetPause(true);
		bShowMouseCursor = true;
	}
}
