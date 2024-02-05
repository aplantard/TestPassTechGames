// Fill out your copyright notice in the Description page of Project Settings.


#include "Pasteque.h"
#include "PastequePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InputMappingContext.h"
#include "Engine/World.h"

// Sets default values
APasteque::APasteque()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pastequeMesh"));
	MeshComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("mainCamera"));
	PlayerCamera->SetupAttachment(SpringArmComponent);

	CharacterMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("characterMovement"));
}

// Called when the game starts or when spawned
void APasteque::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APasteque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector SpringArmLocation = SpringArmComponent->GetComponentLocation();
	FVector MeshLocation = MeshComponent->GetComponentLocation();
	
	float AppDeltaTime = GetWorld()->GetDeltaSeconds();

	FVector NewWorldLocation = FMath::VInterpTo(SpringArmLocation, MeshLocation, AppDeltaTime, 2.0f);

	SpringArmComponent->SetWorldLocation(NewWorldLocation);

}

// Called to bind functionality to input
void APasteque::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APastequePlayerController* PlayerController = Cast<APastequePlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->ClearAllMappings();

				if (!InputMapping.IsNull())
				{
					InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 100);
				}
			}
		}
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (MoveInputAction)
	{
		Input->BindAction(MoveInputAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &APasteque::Move);
	}

	if (RotateInputAction)
	{
		Input->BindAction(RotateInputAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &APasteque::Rotate);
	}

}

void APasteque::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	FVector ForwardVector = PlayerCamera->GetForwardVector();
	FVector RightVector = PlayerCamera->GetRightVector();

	FVector UpDownVector = FVector(ForwardVector.X, ForwardVector.Y, 0);
	FVector RightLeftVector = FVector(RightVector.X, RightVector.Y, 0);

	MeshComponent->AddForce(UpDownVector * (MovementVector.Y * MovementSpeed));
	MeshComponent->AddForce(RightLeftVector * (MovementVector.X * MovementSpeed));

	AddMovementInput(UpDownVector, MovementVector.Y * MovementSpeed);
	AddMovementInput(RightLeftVector, MovementVector.X * MovementSpeed);
}

void APasteque::Rotate(const FInputActionValue& Value)
{
	float RotateValue = Value.Get<float>();
	SpringArmComponent->AddWorldRotation(FRotator(0, RotateValue * RotationSpeed, 0));
}


