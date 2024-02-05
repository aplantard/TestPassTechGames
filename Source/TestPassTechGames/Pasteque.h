// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pasteque.generated.h"

class USpringArmComponent;
class UStaticMeshComponent;
class UInputMappingContext;
class UCameraComponent;
class UInputAction;
class UFloatingPawnMovement;
struct FInputActionValue;

UCLASS()
class TESTPASSTECHGAMES_API APasteque : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APasteque();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* CharacterMovement;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RotateInputAction;

	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);

};
