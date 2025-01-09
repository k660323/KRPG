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

	// 생성자에서 받아옴 정보는
	// 스킬 상세 정보
	// 스킬 이름
	// 스킬 이미지
	// 스킬 레벨
	// 스킬 설명
	// 스킬 쿨타임
	// 스킬 소모량
	// 스킬 데미지 계산방식(str,int,dex,luk)
	// 스킬 몽타주
	
	// 스킬 구현
	// 해당 조건 체크
	// 데미지 계산방식에 따라 데미지를 어떻게 줄지 함수로 구현
	// 1. 근거리 히트박스 정의
	// 2. 투사체 생성 초기화
	// 몽타주 생성 처리

	virtual bool OnCheckEnterState() { return true; }
	virtual void OnEnterState() {}	
	virtual void OnTickState();
	virtual void OnExitState(ECreatureState post) {}
	virtual void OnAttack();
	virtual float DamageLogic() { return 0.0; };
};
