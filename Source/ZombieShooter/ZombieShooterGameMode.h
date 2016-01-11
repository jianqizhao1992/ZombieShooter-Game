// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "ZombieShooterGameMode.generated.h"




/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API AZombieShooterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZombieShooter")
	TSubclassOf<class UUserWidget> StartingWidgetClass;
	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	class UUserWidget* CurrentWidget;
};
