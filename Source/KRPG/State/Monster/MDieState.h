// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "MDieState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UMDieState : public UBaseState
{
	GENERATED_BODY()

private:
	float DestroyTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DieAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* DieMontages;
public:
	UMDieState();

	virtual void Init(AController* pc, UAnimMontage* montages) override;

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;
};
