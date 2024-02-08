// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MainMenuPlayerController.h"

void AMenuGameMode::InitGameState()
{
	Super::InitGameState();

	// Set Default Player Controller

	if (PlayerControllerClass == AMainMenuPlayerController::StaticClass())
	{
		PlayerControllerClass = PlayerController;
	}
}