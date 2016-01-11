// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ZOMBIESHOOTER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Create root component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	USceneComponent *PickupRoot;

	/* Create collision sphere and attach to the root */

	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
