// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMonster.h"
#include "WizardGoblin.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API AWizardGoblin : public ACharacterMonster
{
	GENERATED_BODY()
	
public:
	AWizardGoblin();
	virtual bool InitStat(ECreatureMonster _InitType) override;
	virtual void InitAIController() override;
	virtual void InitPawnSensing() override;
	virtual void AllocatedMachine() override;
	virtual FVector GetCombatSocketLocation() override;
};
