// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterDamageHandler.generated.h"

UINTERFACE(Blueprintable)
class ZOMBIESHOOTER_API UCharacterDamageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICharacterDamageInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Base Character")
	virtual void ReceiveDamage(float Damage);
};