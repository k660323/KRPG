// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardGoblin.h"
#include "Components/CapsuleComponent.h"
#include "Stat.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterAIControllerBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "MIdleState.h"
#include "MRangedAttackState.h"
#include "MDieState.h"
#include "MChaseState.h"
#include "MReturnState.h"
#include "MPatrolState.h"
#include "Projectile.h"
#include "MHitState.h"

AWizardGoblin::AWizardGoblin()
{
	type = ECreatureMonster::WizardGoblin;

	GetCapsuleComponent()->SetCapsuleHalfHeight(65.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> cMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Goblin/Mesh/Epic_skeleton/SK_Epic_Goblin.SK_Epic_Goblin'"));
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

bool AWizardGoblin::InitStat(ECreatureMonster _InitType)
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

void AWizardGoblin::InitAIController()
{
	// 설정 안하면 기본값
	AMonsterAIControllerBase* macb = Cast<AMonsterAIControllerBase>(GetController());
	macb->SpawnPos = GetActorLocation();
	macb->MaxChaseDistance = 3000.f;
	macb->atkRadius = 500.f;
	macb->PatrolRadius = 500.f;
}

void AWizardGoblin::InitPawnSensing()
{
	pawnSensing->SetPeripheralVisionAngle(45.f);
	pawnSensing->HearingThreshold = 1300.f;
	pawnSensing->SightRadius = 1500.f;

	pawnSensing->SetComponentTickEnabled(true);
}

void AWizardGoblin::AllocatedMachine()
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
	
	// 이거 바꾸기
	UAnimMontage* AtkMontage = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Montage/Goblin/AM_RangedAttack.AM_RangedAttack'"));
	// 플프 액터 이런씩으로
	UBlueprint* actorBP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actor/Projectile/BP_TestProjectile.BP_TestProjectile'")));
	//UObject* actorBP = StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actor/Projectile/BP_TestProjectile.BP_TestProjectile'"));
	//UObject* actorBP = LoadObject<UObject>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actor/Projectile/BP_TestProjectile.BP_TestProjectile'"));
	if (AtkMontage && actorBP)
	{
		state = NewObject<UMRangedAttackState>();
		state->Init(macb, FVector(30.f, 30.f, 30.f), AtkMontage, actorBP->GeneratedClass);
		StateMachineComponent->AddState(ECreatureState::Attack, state);
	}

	// 바꾸고 싶으면 바꾸기
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

FVector AWizardGoblin::GetCombatSocketLocation()
{
	check(Weapon);

	return Weapon->GetSocketLocation(WeaponTipSocketName);
}
