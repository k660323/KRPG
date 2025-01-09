// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/Player/AttackState.h"
#include "CountessAttackState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UCountessAttackState : public UAttackState
{
	GENERATED_BODY()
	
public:
	UCountessAttackState();

	virtual void OnAttack() override;
};
