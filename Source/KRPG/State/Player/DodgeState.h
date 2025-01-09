// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "DodgeState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UDodgeState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RollAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D InputValue;
public:
	UDodgeState();

	virtual void Init(AController* pc, UAnimMontage* montages) override;

	virtual bool OnCheckEnterState() override;

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;
};
