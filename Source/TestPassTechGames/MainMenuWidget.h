// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UTextBlock;
class ULevel;

/**
 * 
 */
UCLASS(abstract)
class TESTPASSTECHGAMES_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StartButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();
	
};
