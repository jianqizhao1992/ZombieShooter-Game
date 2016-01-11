// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieShooter.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up temp gun location and attach to root
	GunTempLoc = CreateDefaultSubobject<UArrowComponent>(TEXT("GunTempLoc"), false);
	GunTempLoc->AttachTo(this->GetMesh());

	// Find the class to Gun blueprint
	static ConstructorHelpers::FObjectFinder<UBlueprint> GunBlueprintRaw(TEXT("Blueprint'/Game/Blueprints/Gun.Gun'"));
	if (GunBlueprintRaw.Object) {
		GunBlueprintClass = (UClass *)GunBlueprintRaw.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (this->isHero)
	{
		const FTransform GunSpawnPoint = this->GunTempLoc->GetComponentTransform();
		GunBlueprintInstance = GetWorld()->SpawnActor(GunBlueprintClass, &GunSpawnPoint);
		
		//GunBlueprintInstance->AttachRootComponentTo(this->GunTempLoc, NAME_None, EAttachLocation::SnapToTarget);
		GunBlueprintInstance->AttachRootComponentTo(GetMesh(), TEXT("Gun_socket"), EAttachLocation::SnapToTarget);

		this->GunBlueprintAWeaponInstance = (AWeapon *)GunBlueprintInstance;
	}
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAxis("MoveUp", this, &ABaseCharacter::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	InputComponent->BindAxis("MoveCursor", this, &ABaseCharacter::MoveCursor);
	InputComponent->BindAction("PullTrigger", IE_Pressed, this, &ABaseCharacter::PullTrigger);
	InputComponent->BindAction("ReleaseTrigger", IE_Released, this, &ABaseCharacter::ReleaseTrigger);

}

void ABaseCharacter::CalculateHealth(float Delta)
{
	Health += Delta;
	CalculateDead();
}

void ABaseCharacter::CalculateDead()
{
	if (Health <= 0)
		isDead = true;
	else
		isDead = false;
}

void ABaseCharacter::ReceiveDamage()
{
	isDead = true;
	if (Controller != NULL)
	{
		Controller->Destroy();
	}
	this->SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(DeadDelayTimeHandle, this, &ABaseCharacter::DestroyActor, 1.0f, false, 1.5f);
	//this->Destroy();
}

void ABaseCharacter::DestroyActor()
{
	this->Destroy();
}

void ABaseCharacter::MoveUp(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddMovementInput(FVector::ForwardVector, Value);	
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddMovementInput(FVector::RightVector, Value);
	}
}

void ABaseCharacter::MoveCursor(float Value)
{
	RotateCharacter();
}

void ABaseCharacter::PullTrigger_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle, this, &ABaseCharacter::FireGun, 0.15, true, 0);
}

bool ABaseCharacter::PullTrigger_Validate()
{
	return true;
}

void ABaseCharacter::ReleaseTrigger_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimeHandle);
}

bool ABaseCharacter::ReleaseTrigger_Validate()
{
	return true;
}

void ABaseCharacter::FireGun_Implementation()
{
	if (EnergyLevel > 0) {
		this->GunBlueprintAWeaponInstance->Fire();
		EnergyLevel--;
	}
}

bool ABaseCharacter::FireGun_Validate()
{
	return true;
}

void ABaseCharacter::RotateCharacter()
{
	float CursorX = 0;
	float CursorY = 0;
	auto PControl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PControl->bShowMouseCursor = true;
	PControl->GetMousePosition(CursorX, CursorY);
	FVector CursorLocation = FVector(CursorX, CursorY, 0);
	
	// Get Actor Screen Location
	FVector ActorScreenLocation = FVector(this->GetCharacterLocationX(), this->GetCharacterLocationY(), 0);

	FRotator Rot = FRotationMatrix::MakeFromZ(CursorLocation - ActorScreenLocation).Rotator();
	Controller->SetControlRotation(Rot);
}

#if WITH_EDITOR
void ABaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	isDead = false;
	Health = 100;

	Super::PostEditChangeProperty(PropertyChangedEvent);

	CalculateDead();
}

#endif


// Get Character(Player)'s location
float ABaseCharacter::GetCharacterLocationX()
{
	auto PControl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector ActorWorldLocation = this->GetActorLocation();
	FVector2D ActorScreenLocation;
	PControl->ProjectWorldLocationToScreen(ActorWorldLocation, ActorScreenLocation);
	return ActorScreenLocation.X;
}

float ABaseCharacter::GetCharacterLocationY()
{
	auto PControl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector ActorWorldLocation = this->GetActorLocation();
	FVector2D ActorScreenLocation;
	PControl->ProjectWorldLocationToScreen(ActorWorldLocation, ActorScreenLocation);
	return ActorScreenLocation.Y;
}

// Replicate EnergyLevel variable
void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, EnergyLevel);
}