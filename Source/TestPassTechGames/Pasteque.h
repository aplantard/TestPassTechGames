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
class USphereComponent;
class UArrowComponent;
class UAudioComponent;
class ASpell;
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
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* SpellSpawnPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponentSound;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pasteque", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Jump", meta = (AllowPrivateAccess = "true"))
	float MaxZVelocity = 150.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Jump", meta = (AllowPrivateAccess = "true"))
	float JumpPower = 5.f;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RotateInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> ShootInputAction;

	UPROPERTY(EditAnywhere, Category = "SFX")
	TSoftObjectPtr<USoundBase> BounceSound;

	UPROPERTY(EditAnywhere, Category = "SFX")
	TSoftObjectPtr<USoundBase> SpellSound;

	UPROPERTY(EditAnywhere, Category = "Spell")
	TSubclassOf<ASpell> SpellToThrow;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	float InitialCameraHeight = 0.f;
	float NewCameraHeight = 0.f;
	FVector LastBounceDirection = FVector(0, 0, 1);
	FVector LastBounceLocation = FVector();

	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

};
