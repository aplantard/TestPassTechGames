// Fill out your copyright notice in the Description page of Project Settings.


#include "Pasteque.h"
#include "PastequePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Spell.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "InputMappingContext.h"
#include "Engine/World.h"

// Sets default values
APasteque::APasteque()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComponent"));
	SphereCollision->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pastequeMesh"));
	MeshComponent->OnComponentHit.AddDynamic(this, &APasteque::OnHit);
	MeshComponent->SetupAttachment(SphereCollision);

	AudioComponentSound = CreateDefaultSubobject<UAudioComponent>(TEXT("audioComponent"));
	AudioComponentSound->bAutoActivate = false;
	AudioComponentSound->SetupAttachment(MeshComponent);

	SpellSpawnPos = CreateDefaultSubobject<UArrowComponent>(TEXT("spellSpawnPos"));
	SpellSpawnPos->SetupAttachment(MeshComponent);

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

	InitialCameraHeight = SpringArmComponent->GetRelativeLocation().Z;
	NewCameraHeight = InitialCameraHeight;
}

// Called every frame
void APasteque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector SpringArmLocation = SpringArmComponent->GetComponentLocation();
	FVector SpringArmRelativeLocation = SpringArmComponent->GetRelativeLocation();
	FVector MeshLocation = MeshComponent->GetComponentLocation();

	if ((MeshLocation.Z - LastBounceLocation.Z) >= MaxJumpHeight)
	{
		FVector PastequeVelocity = MeshComponent->GetPhysicsLinearVelocity();
		MeshComponent->SetPhysicsLinearVelocity(FVector(PastequeVelocity.X, PastequeVelocity.Y, 0));
	}

	// Move Camera To Watermelon
	float AppDeltaTime = GetWorld()->GetDeltaSeconds();

	FVector NewWorldLocation = FMath::VInterpTo(SpringArmLocation, MeshLocation, AppDeltaTime, 2.0f);
	float NewHeight = SpringArmLocation.Z;
	
	if (FMath::Abs(NewCameraHeight - SpringArmLocation.Z) > 0.001f)
	{
		NewHeight = FMath::FInterpTo(SpringArmLocation.Z, NewCameraHeight, AppDeltaTime, 2.0f);
	}

	SpringArmComponent->SetWorldLocation(FVector(NewWorldLocation.X, NewWorldLocation.Y, NewHeight));

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

	if (JumpInputAction)
	{
		Input->BindAction(JumpInputAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &APasteque::Jump);
	}

	if (ShootInputAction)
	{
		Input->BindAction(ShootInputAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &APasteque::Shoot);
	}

}

void APasteque::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LastBounceDirection = Hit.ImpactNormal;
	LastBounceLocation = Hit.ImpactPoint;

	if (LastBounceLocation.Z != NewCameraHeight)
	{
		NewCameraHeight = InitialCameraHeight + LastBounceLocation.Z;
	}

	USoundBase* LocalBounceSound = BounceSound.LoadSynchronous();

	if (AudioComponentSound->GetSound() != LocalBounceSound)
	{
		AudioComponentSound->SetSound(LocalBounceSound);
	}
	
	AudioComponentSound->Play();
}

void APasteque::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>() * MovementSpeed;

	FVector ForwardVector = SpringArmComponent->GetForwardVector();
	FVector RightVector = SpringArmComponent->GetRightVector();

	FVector UpDownVector = FVector::VectorPlaneProject(ForwardVector, FVector(0, 0, 1));
	FVector RightLeftVector = FVector::VectorPlaneProject(RightVector, FVector(0, 0, 1));

	MeshComponent->AddForce(UpDownVector * MovementVector.Y, FName(), true);
	MeshComponent->AddForce(RightLeftVector * MovementVector.X, FName(), true);

	FVector PastequeVelocity = MeshComponent->GetPhysicsLinearVelocity();
	MeshComponent->SetPhysicsLinearVelocity(FVector(PastequeVelocity.X * 0.96, PastequeVelocity.Y * 0.96, PastequeVelocity.Z));
}

void APasteque::Rotate(const FInputActionValue& Value)
{
	float RotateValue = Value.Get<float>();
	SpringArmComponent->AddWorldRotation(FRotator(0, RotateValue * RotationSpeed, 0));
	MeshComponent->AddWorldRotation(FRotator(0, RotateValue * RotationSpeed, 0));
}

void APasteque::Jump(const FInputActionValue& Value)
{
	FVector MeshLocation = MeshComponent->GetComponentLocation();

	if ((MeshLocation.Z - LastBounceLocation.Z) < MaxJumpHeight)
	{
		float JumpValue = Value.Get<float>();

		FVector PastequeVelocity = MeshComponent->GetPhysicsLinearVelocity();
		MeshComponent->SetPhysicsLinearVelocity(PastequeVelocity * (JumpValue * JumpPower), false, FName());
	}
}

void APasteque::Shoot(const FInputActionValue& Value)
{
	FVector SpawnLocation = SpellSpawnPos->GetComponentLocation();
	FRotator SpawnRotation = SpellSpawnPos->GetComponentRotation();

	GetWorld()->SpawnActor(SpellToThrow, &SpawnLocation, &SpawnRotation, FActorSpawnParameters());

	USoundBase* LocalSpellSound = SpellSound.LoadSynchronous();

	if (AudioComponentSound->GetSound() != LocalSpellSound)
	{
		AudioComponentSound->SetSound(LocalSpellSound);
	}

	AudioComponentSound->Play();
}
