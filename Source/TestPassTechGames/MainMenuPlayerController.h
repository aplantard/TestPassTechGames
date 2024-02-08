// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class TESTPASSTECHGAMES_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

public: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
	UUserWidget* WidgetInstance;
};
