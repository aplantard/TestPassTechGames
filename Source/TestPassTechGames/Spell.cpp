// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent >(TEXT("projectileMovementComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spellMesh"));
	MeshComponent->OnComponentHit.AddDynamic(this, &ASpell::OnHit);

	AudioComponentSound = CreateDefaultSubobject<UAudioComponent>(TEXT("audioComponent"));
	AudioComponentSound->bAutoActivate = false;
	AudioComponentSound->SetupAttachment(MeshComponent);

	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpell::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();

	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		OtherActor->Destroy();

		USoundBase* LocalEnemySound = HitEnemeySound.LoadSynchronous();

		if (AudioComponentSound->GetSound() != LocalEnemySound)
		{
			AudioComponentSound->SetSound(LocalEnemySound);
		}

		AudioComponentSound->Play();
	}
}

