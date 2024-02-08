// Fill out your copyright notice in the Description page of Project Settings.


#include "PastequePlayerController.h"

void APastequePlayerController::BeginPlay()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}