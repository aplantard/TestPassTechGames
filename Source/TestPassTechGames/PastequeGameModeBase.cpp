// Fill out your copyright notice in the Description page of Project Settings.


#include "PastequeGameModeBase.h"

#include "Pasteque.h"
#include "PastequePlayerController.h"

void APastequeGameModeBase::InitGameState()
{
	Super::InitGameState();

	// Set Default pawn

	if (DefaultPawnClass == APasteque::StaticClass())
	{
		DefaultPawnClass = Pasteque;
	}

	// Set Default Player Controller

	if (PlayerControllerClass == APastequePlayerController::StaticClass())
	{
		PlayerControllerClass = PlayerController;
	}
}
