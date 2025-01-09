// Fill out your copyright notice in the Description page of Project Settings.


#include "Countess.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KRPGAssetManager.h"
#include "Stat.h"
#include "PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "StatDataTable.h"
#include "StateMachineComponent.h"
#include "IdleState.h"
#include "MoveState.h"
#include "RollState.h"
#include "CountessAttackState.h"
#include "JumpState.h"
#include "DodgeState.h"
#include "TakeDownState.h"
#include "CrossSlashState.h"
#include "KRPGGameplayTags.h"
#include "UltimateSkillState.h"
#include "SpineDownState.h"

#include <Define.h>

ACountess::ACountess()
{
	type = ECreaturePlayer::Countness;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> cMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'"));
	if (cMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(cMesh.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -88.f), FRotator(0, -90.f, 0));
	}

	stat = CreateDefaultSubobject<UStat>(TEXT("stat"));
}

void ACountess::AllocatedMachine()
{
	APlayerControllerBase* acb = Cast<APlayerControllerBase>(GetController());

	TObjectPtr<UBaseState> state = NewObject<UIdleState>();
	state->Init(acb);
	StateMachineComponent->InitState(ECreatureState::Idle, state);

	state = NewObject<UMoveState>();
	state->Init(acb);
	StateMachineComponent->AddState(ECreatureState::Move, state);

	state = NewObject<UCountessAttackState>();
	state->Init(acb, FVector(50.f, 50.f, 85.f));
	StateMachineComponent->AddState(ECreatureState::Attack, state);

	state = NewObject<UJumpState>();
	state->Init(acb);
	StateMachineComponent->AddState(ECreatureState::Jump, state);


	UAnimMontage* RollMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_Roll.AM_Roll'"));
	if (RollMontage)
	{
		state = NewObject<URollState>();
		state->Init(acb, RollMontage);
		StateMachineComponent->AddState(ECreatureState::Roll, state);
	}
	
	
	UAnimMontage* DodgeMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Countess/AM_Dodge.AM_Dodge'"));
	if (DodgeMontage)
	{
		state = NewObject<UDodgeState>();
		state->Init(acb, DodgeMontage);
		StateMachineComponent->AddState(ECreatureState::Dodge, state);
	}

	// skill
	state = NewObject<UTakeDownState>();
	state->Init(acb);
	StateMachineComponent->AddSkillState(FKRPGGameplayTags::Get().InputTag_Q, state);

	// skill
	state = NewObject<UCrossSlashState>();
	state->Init(acb);
	StateMachineComponent->AddSkillState(FKRPGGameplayTags::Get().InputTag_E, state);

	// skill
	state = NewObject<UUltimateSkillState>();
	state->Init(acb);
	StateMachineComponent->AddSkillState(FKRPGGameplayTags::Get().InputTag_G, state);

	// skill
	state = NewObject<USpineDownState>();
	state->Init(acb);
	StateMachineComponent->AddSkillState(FKRPGGameplayTags::Get().InputTag_RMB, state);
}

bool ACountess::InitStat(int index)
{
	// 오버드라이브 안할시 기본 적용 값 적용
	// 데이터 가져오기
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FStatData* data = UKRPGAssetManager::Get().GetPlayerStatDataTable(type, index);

	if (data == nullptr)
		return false;

	stat.Get()->OnRotationChanged.AddUniqueDynamic(this, &ACharacterBase::BindCharacterMovement);
	stat.Get()->OnJumpZVelocityChanged.AddUniqueDynamic(this, &ACharacterBase::BindJumpZVelocity);
	stat.Get()->OnAirControlChanged.AddUniqueDynamic(this, &ACharacterBase::BindAirControl);
	stat.Get()->OnMaxWalkSpeedChanged.AddUniqueDynamic(this, &ACharacterBase::BindMaxWalkSpeed);
	stat.Get()->OnMinWalkSpeedChanged.AddUniqueDynamic(this, &ACharacterBase::BindMinAnalogWalkSpeed);
	stat.Get()->OnJumpCountChanged.AddUniqueDynamic(this, &ACharacterBase::BindJumpMaxCount);
	
	stat.Get()->SetLevel(data->Level);
	stat.Get()->SetMaxHp(data->MaxHp);
	stat.Get()->SetCurHp(data->MaxHp + stat->GetAdditiveMaxHp());
	stat.Get()->SetMaxMp(data->MaxMp);
	stat.Get()->SetCurMp(data->MaxMp + stat->GetAdditiveMaxMp());
	stat.Get()->SetJumpCount(data->JumpCount);
	stat.Get()->SetPhysicalAttack(data->PhysicalAttack);
	stat.Get()->SetMagicAttack(data->MagicAttack);
	stat.Get()->SetPhysicalDefence(data->PhysicalDefence);
	stat.Get()->SetMagicDefence(data->MagicDefence);
	stat.Get()->SetSTR(stat.Get()->GetSTR() + data->STR);
	stat.Get()->SetINT(stat.Get()->GetINT() + data->INT);
	stat.Get()->SetDEX(stat.Get()->GetDEX() + data->DEX);
	stat.Get()->SetLUK(stat.Get()->GetLUK() + data->LUK);
	stat.Get()->SetCurStatCount(stat.Get()->GetCurStatCount() + data->StatCount);
	stat.Get()->SetHpRecovery(data->HpRecovery);
	stat.Get()->SetMpRecovery(data->MpRecovery);
	stat.Get()->SetExp(0);
	stat.Get()->SetMaxExp(data->MaxExp);
	stat.Get()->SetAtkSpeed(data->AtkSpeed);
	stat.Get()->SetCritical(data->Critical);
	stat.Get()->SetRotationRate(data->RotationRate);
	stat.Get()->SetJumpZVelocity(data->JumpZVelocity);
	stat.Get()->SetAirControl(data->AirControl);
	stat.Get()->SetMaxWalkSpeed(data->MaxWalkSpeed);
	stat.Get()->SetMinAnalogWalkSpeed(data->MinAnalogWalkSpeed);

	return true;
}

