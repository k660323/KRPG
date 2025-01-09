// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "AttackState.generated.h"

class AController;
class UAnimMontage;
/**
 * 
 */
UCLASS()
class KRPG_API UAttackState : public UBaseState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool SaveAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool bWeaponActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		FVector attackSize;

	UPROPERTY()
		TSet<AActor*> WeaponAttackTargets;
public:
	UAttackState();

	// 根鸥林 积己磊俊辑 持绢林扁
	virtual void Init(AController* pc, FVector atkSize) override;
	// 根鸥林 持绢林扁
	virtual void Init(AController* pc, FVector atkSize, UAnimMontage* montage) override;

	virtual void OnEnterState() override;
	virtual void OnTickState() override;
	virtual void OnExitState(ECreatureState post) override;

	UFUNCTION()
	virtual void OnAttack();

	UFUNCTION(BlueprintCallable)
		int32 GetAttackCount()
	{
		return AttackCount;
	}

	UFUNCTION(BlueprintCallable)
		void SetAttackCount(int Value)
	{
		AttackCount = FMath::Max(0, Value);
	}

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking()
	{
		return IsAttacking;
	}

	UFUNCTION(BlueprintCallable)
		void SetIsAttacking(bool Value)
	{
		IsAttacking = Value;
	}

	UFUNCTION(BlueprintCallable)
		bool GetSaveAttack()
	{
		return SaveAttack;
	}

	UFUNCTION(BlueprintCallable)
		void SetSaveAttack(bool Value)
	{
		SaveAttack = Value;
	}

	UFUNCTION(BlueprintCallable)
		bool GetWeaponActive()
	{
		return bWeaponActive;
	}

	UFUNCTION(BlueprintCallable)
		void SetWeaponActive(bool Value)
	{
		bWeaponActive = Value;
	}
};
