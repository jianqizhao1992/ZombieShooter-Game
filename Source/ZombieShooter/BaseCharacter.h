// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "CharacterDamageHandler.h"
#include "UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS()
class ZOMBIESHOOTER_API ABaseCharacter : public ACharacter, public ICharacterDamageInterface
{
	GENERATED_BODY()

	// Set up pointer to Gun blueprint instance
	UPROPERTY(VisibleAnywhere, Category = "Base Character")
	AActor *GunBlueprintInstance;

	// Set up pointer to Gun blueprint instance for First Person
	UPROPERTY(VisibleAnywhere, Category = "Base Character")
	AActor *GunBlueprintInstanceFirstPerson;

	UPROPERTY(VisibleAnywhere, Category = "Base Character")
	AWeapon *GunBlueprintAWeaponInstance;

	/* Pointer to player controller */
	APlayerController *PControl = NULL;

	FTimerHandle FireTimeHandle;
	FTimerHandle DeadDelayTimeHandle;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	bool HighCameraActive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	float Health = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Character")
	bool isDead = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	bool isHero = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated, Category = "Base Character")
	float EnergyLevel = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	UArrowComponent *GunTempLoc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	UArrowComponent *GunTempLocFirstPerson;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	USkeletalMeshComponent *MeshFirstPerson;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimation;

	// Set up Gun blueprint class pointer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UClass *GunBlueprintClass;

	virtual void CalculateDead();

	virtual void ReceiveDamage();

	void DestroyActor();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateHealth(float delta);

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	float GetCharacterLocationX();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	float GetCharacterLocationY();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
#endif

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void MoveUp(float Value);

	void MoveRight(float Value);

	void MoveCursorRight(float Value);

	void MoveCursorUp(float Value);

	UFUNCTION(Server, reliable, WithValidation)
	void PullTrigger();

	UFUNCTION(Server, reliable, WithValidation)
	void ReleaseTrigger();

	UFUNCTION(Server, reliable, WithValidation)
	void FireGun();

	UFUNCTION(BlueprintImplementableEvent, Category = "Base Character")
	void ToggleCamera();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	void SwitchCamera(UPARAM(ref) UActorComponent*& Camera1, UPARAM(ref) UActorComponent*& Camera2);

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	void SwitchGun();

	void RotateCharacter();


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
