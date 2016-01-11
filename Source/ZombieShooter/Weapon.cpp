// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieShooter.h"
#include "Weapon.h"
#include "Projectile.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up root component
	WeaponRoot = AWeapon::CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"), false);
	RootComponent = WeaponRoot;

	// Set up Gun mesh and attach to root
	GunMesh = AWeapon::CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"), false);
	GunMesh->AttachTo(RootComponent);

	// Set up Projectile spawn point and attach to gun mesh
	ProjectileSpawnPoint = AWeapon::CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"), false);
	ProjectileSpawnPoint->AttachTo(GunMesh);

	// Find Projectile Blueprint class
	static ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBlueprintRaw(TEXT("Blueprint'/Game/Blueprints/ProjectileBlueprint.ProjectileBlueprint'"));
	if (ProjectileBlueprintRaw.Object) {
		ProjectileBlueprintClass = (UClass *)ProjectileBlueprintRaw.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AWeapon::Fire()
{
	const FTransform ProjectileSpawnPoint = this->ProjectileSpawnPoint->GetComponentTransform();
	//FRotator ProjectileSpawnRotation = FRotator(ProjectileSpawnPoint.GetRotation());
	//FVector ProjectileSpawnLocation = ProjectileSpawnPoint.GetLocation();
	GetWorld()->SpawnActor(ProjectileBlueprintClass, &ProjectileSpawnPoint);
}