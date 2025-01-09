// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/Skill/SkillState.h"
#include "SpineDownState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API USpineDownState : public USkillState
{
	GENERATED_BODY()
	
public:
	USpineDownState();

	virtual bool OnCheckEnterState() override;
	virtual void OnEnterState() override;
	virtual void OnExitState(ECreatureState post) override;
	virtual void OnAttack() override;
	virtual float DamageLogic() override;
};
