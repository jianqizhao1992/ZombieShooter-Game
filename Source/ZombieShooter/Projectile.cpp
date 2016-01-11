// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieShooter.h"
#include "Projectile.h"
#include "CharacterDamageHandler.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set up root component
	ProjectileRoot = AProjectile::CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"), false);
	RootComponent = ProjectileRoot;

	// Set up Sphere, SphereCollision and attach to root
	SphereCollision = AProjectile::CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"), false);
	SphereCollision->AttachTo(RootComponent);

	Sphere = AProjectile::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"), false);
	Sphere->AttachTo(RootComponent);

	// Set up Movement Component
	ProjectileMovement = AProjectile::CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"), false);

	// Bind Actor Overlap Component
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileOverlapBegin);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called when project overlap other actor
UFUNCTION()
void AProjectile::OnProjectileOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != NULL || OtherComp != NULL)
	{
		this->Destroy();
		if (OtherActor->GetClass()->ImplementsInterface(UCharacterDamageInterface::StaticClass()))
		{
			ICharacterDamageInterface *InterfaceActor = Cast<ICharacterDamageInterface>(OtherActor);
			InterfaceActor->ReceiveDamage();
			//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("shot"));
		}
	}
}