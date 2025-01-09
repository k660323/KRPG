// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "MPatrolState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UMPatrolState : public UBaseState
{
	GENERATED_BODY()

public:
	UMPatrolState();

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
};
