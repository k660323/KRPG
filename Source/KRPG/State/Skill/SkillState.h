// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/BaseState.h"
#include "Define.h"
#include "SkillState.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API USkillState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAnim", meta = (AllowPrivateAccess = "true"))
		FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAnim", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool bWeaponActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		FVector attackSize;

	UPROPERTY()
		TSet<AActor*> WeaponAttackTargets;
public:
	USkillState();

	// �����ڿ��� �޾ƿ� ������
	// ��ų �� ����
	// ��ų �̸�
	// ��ų �̹���
	// ��ų ����
	// ��ų ����
	// ��ų ��Ÿ��
	// ��ų �Ҹ�
	// ��ų ������ �����(str,int,dex,luk)
	// ��ų ��Ÿ��
	
	// ��ų ����
	// �ش� ���� üũ
	// ������ ����Ŀ� ���� �������� ��� ���� �Լ��� ����
	// 1. �ٰŸ� ��Ʈ�ڽ� ����
	// 2. ����ü ���� �ʱ�ȭ
	// ��Ÿ�� ���� ó��

	virtual bool OnCheckEnterState() { return true; }
	virtual void OnEnterState() {}	
	virtual void OnTickState();
	virtual void OnExitState(ECreatureState post) {}
	virtual void OnAttack();
	virtual float DamageLogic() { return 0.0; };
};
