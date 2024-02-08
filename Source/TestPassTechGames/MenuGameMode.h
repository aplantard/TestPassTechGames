// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"


class AMainMenuPlayerController;

/**
 * 
 */
UCLASS()
class TESTPASSTECHGAMES_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void InitGameState() override;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMainMenuPlayerController> PlayerController;
};
