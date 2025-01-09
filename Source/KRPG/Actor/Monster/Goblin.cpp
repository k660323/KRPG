// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"
#include "MonsterAIControllerBase.h"
#include "StateMachineComponent.h"
#include "Components/CapsuleComponent.h"
#include "KRPGAssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Stat.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseState.h"
#include "MIdleState.h"
#include "MAttackState.h"
#include "MDieState.h"
#include "MChaseState.h"
#include "MReturnState.h"
#include "MPatrolState.h"
#include "MHitState.h"

AGoblin::AGoblin()
{
	type = ECreatureMonster::Goblin;

	GetCapsuleComponent()->SetCapsuleHalfHeight(65.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> cMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Goblin/Mesh/Goblin_Base/SK_Goblin.SK_Goblin'"));
	if (cMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(cMesh.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -70.f), FRotator(0, -90.f, 0));
	}

	stat = CreateDefaultSubobject<UStat>(TEXT("stat"));

	FTransform spawnPos = GetMesh()->GetSocketTransform(FName("WeaponHandSocket"));
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetWorldTransform(spawnPos);
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->SetComponentTickEnabled(false);
}

bool AGoblin::InitStat(ECreatureMonster _InitType)
{
	FStatData* data = UKRPGAssetManager::Get().GetMonsterStatDataTable(_InitType);
	
	if (data == nullptr)
		return false;

	stat.Get()->SetLevel(data->Level);
	stat.Get()->SetMaxHp(data->MaxHp);
	stat.Get()->SetCurHp(data->MaxHp);
	stat.Get()->SetMaxMp(data->MaxMp);
	stat.Get()->SetCurMp(data->MaxMp);
	stat.Get()->SetJumpCount(data->JumpCount);
	stat.Get()->SetPhysicalAttack(data->PhysicalAttack);
	stat.Get()->SetMagicAttack(data->MagicAttack);
	stat.Get()->SetPhysicalDefence(data->PhysicalDefence);
	stat.Get()->SetMagicDefence(data->MagicDefence);
	stat.Get()->SetSTR(data->STR);
	stat.Get()->SetINT(data->INT);
	stat.Get()->SetDEX(data->DEX);
	stat.Get()->SetLUK(data->LUK);
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

void AGoblin::InitAIController()
{
	Super::InitAIController();
}


void AGoblin::InitPawnSensing()
{
	pawnSensing->SetPeripheralVisionAngle(45.f);
	pawnSensing->HearingThreshold = 1300.f;
	pawnSensing->SightRadius = 1500.f;

	pawnSensing->SetComponentTickEnabled(true);
}

void AGoblin::AllocatedMachine()
{
	AMonsterAIControllerBase* macb = Cast<AMonsterAIControllerBase>(GetController());

	TObjectPtr<UBaseState> state = NewObject<UMIdleState>();
	state->Init(macb);
	StateMachineComponent->InitState(ECreatureState::Idle, state);

	state = NewObject<UMChaseState>();
	state->Init(macb);
	StateMachineComponent->AddState(ECreatureState::Chase, state);

	state = NewObject<UMReturnState>();
	state->Init(macb);
	StateMachineComponent->AddState(ECreatureState::Return, state);

	state = NewObject<UMPatrolState>();
	state->Init(macb);
	StateMachineComponent->AddState(ECreatureState::Patrol, state);

	UAnimMontage* AtkMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Goblin/AM_NormalAttack.AM_NormalAttack'"));
	if (AtkMontage)
	{
		state = NewObject<UMAttackState>();
		state->Init(macb, FVector(30.f, 30.f, 30.f), AtkMontage);
		StateMachineComponent->AddState(ECreatureState::Attack, state);
	}

	UAnimMontage* DieMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Goblin/AM_Die.AM_Die'"));
	if (DieMontage)
	{
		state = NewObject<UMDieState>();
		state->Init(macb, DieMontage);
		StateMachineComponent->AddState(ECreatureState::Die, state);
	}

	UAnimMontage* HitMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Goblin/AM_Hit.AM_Hit'"));
	if (HitMontage)
	{
		state = NewObject<UMHitState>();
		state->Init(macb, HitMontage);
		StateMachineComponent->AddState(ECreatureState::Hit, state);
	}
}

FVector AGoblin::GetCombatSocketLocation()
{
	check(Weapon);

	return Weapon->GetSocketLocation(WeaponTipSocketName);
}
