// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PastequeGameModeBase.generated.h"


class APasteque;
class APastequePlayerController;

/**
 * 
 */
UCLASS()
class TESTPASSTECHGAMES_API APastequeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	void InitGameState() override;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APasteque> Pasteque;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APastequePlayerController> PlayerController;
};
