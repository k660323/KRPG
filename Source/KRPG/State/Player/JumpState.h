// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "JumpState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UJumpState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UJumpState();

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;
};
