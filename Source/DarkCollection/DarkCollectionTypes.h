#pragma once

/*
	Documentation types enumerator for sorting in categories
*/

UENUM()
enum class EDocumentationType : uint8
{
	None UMETA(DisplayName = "None"),
	Document UMETA(DisplayName = "Document"),
	Note UMETA(DisplayName = "Note"),
	Picture UMETA(DisplayName = "Picture"),
};




/*
	Action names for interaction system
*/

const FName ActionInteract = FName("Interact"); 