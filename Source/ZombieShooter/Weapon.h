// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()

	// Set up weapon root
	USceneComponent *WeaponRoot;
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Spawn projectile
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	// Set up project blueprint pointer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UClass *ProjectileBlueprintClass;

	// Set up projectile spawn point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UArrowComponent *ProjectileSpawnPoint;

	// Set up gun mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent *GunMesh;
	
};
