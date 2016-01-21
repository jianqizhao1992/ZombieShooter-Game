// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "ZombieSpawner.generated.h"

UCLASS()
class ZOMBIESHOOTER_API AZombieSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent *ZombieSpawnRootComponent;

public:	
	// Connect to ZombieBlueprintClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZombieSpawner")
	class UClass *ZombieBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZombieSpawner")
	UBoxComponent *SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZombieSpawner")
	FVector ZombieBoxSpawnExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZombieSpawner")
	FVector ZombieBoxSpawnLocation;

	// Sets default values for this actor's properties
	AZombieSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "ZombieSpawner")
	void SpawnZombie();

	UFUNCTION(BlueprintCallable, Category = "ZombieSpawner")
	void SpawnSingleZombie();
	
};
