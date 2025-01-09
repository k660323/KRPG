// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/Skill/SkillState.h"
#include "CrossSlashState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UCrossSlashState : public USkillState
{
	GENERATED_BODY()
	
public:
	UCrossSlashState();

	virtual bool OnCheckEnterState();
	virtual void OnEnterState();
	virtual void OnExitState(ECreatureState post);
	virtual float DamageLogic();
};
