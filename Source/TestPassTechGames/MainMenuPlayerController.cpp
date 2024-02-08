// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	if (WidgetTemplate)
	{
		if (!WidgetInstance)
		{
			WidgetInstance = CreateWidget(this, WidgetTemplate);
			WidgetInstance->AddToViewport();
		}
	}

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}