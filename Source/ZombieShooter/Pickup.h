// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ZOMBIESHOOTER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Root component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	USceneComponent *PickupRoot;

	/* Mesh component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent *PickupMesh;

	/* Collision sphere component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USphereComponent *PickupCollision;

	/* Effective flag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool isEffective = true;

	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
