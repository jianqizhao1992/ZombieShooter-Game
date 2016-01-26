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

public:
	// Set up pointer to Gun blueprint instance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Weapon")
	AActor *GunBlueprintInstanceThirdPerson;

	// Set up pointer to Gun blueprint instance for First Person
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Weapon")
	AActor *GunBlueprintInstanceFirstPerson;

	UPROPERTY(VisibleAnywhere, Category = "Character Weapon")
	AWeapon *CurrentAWeaponInstance;

	/* Pointer to player controller */
	APlayerController *PControl = NULL;

	FTimerHandle FireTimeHandle;
	FTimerHandle DeadDelayTimeHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Status")
	bool HighCameraActive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Status")
	float Health = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character Status")
	bool isDead = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Status")
	bool isHero = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated, Category = "Character Status")
	float EnergyLevel = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	USkeletalMeshComponent *MeshFirstPerson;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimation;

	// Set up Gun blueprint class pointer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UClass *GunBlueprintClass;

	virtual void CalculateDead();

	virtual void DestroyCharacter();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void ReceiveDamage(float Damage);

	void DestroyActor();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateHealth(float delta);

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateAmmo(float delta);

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	float GetCharacterLocationX();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	float GetCharacterLocationY();

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

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
#endif

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
