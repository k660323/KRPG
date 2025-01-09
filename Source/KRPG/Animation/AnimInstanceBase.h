// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include <Define.h>
#include "AnimInstanceBase.generated.h"

class ACharacterBase;
class UCharacterMovementComponent;
class UAnimMontage;
class UStateMachineComponent;

/**
 * 
 */
UCLASS()
class KRPG_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<ACharacterBase> Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		ECreatureState CurState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStateMachineComponent> StateMachineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FRotator RotationLastTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float YawDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool IsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blueprint, meta = (AllowPrivateAccess = "true"))
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blueprint, meta = (AllowPrivateAccess = "true"))
		int CurrentAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blueprint, meta = (AllowPrivateAccess = "true"))
		bool FullBody;
};
