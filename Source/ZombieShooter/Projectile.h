// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
//#include "BaseCharacter.h"
#include "Projectile.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	USceneComponent *ProjectileRoot;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Collision sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	USphereComponent *SphereCollision;
	
	// Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UStaticMeshComponent *Sphere;
	
	// Movement Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FComponentBeginOverlapSignature OnComponentBeginOverlap;

	UFUNCTION()
	void OnProjectileOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
