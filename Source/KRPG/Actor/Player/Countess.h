// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterPlayer.h"
#include "Countess.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API ACountess : public ACharacterPlayer
{
	GENERATED_BODY()
	
public:
	ACountess();
	virtual void AllocatedMachine() override;
	virtual bool InitStat(int index) override;
};
