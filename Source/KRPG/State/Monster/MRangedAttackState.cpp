// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Monster/MRangedAttackState.h"
#include "Projectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterAIControllerBase.h"
#include "CharacterBase.h"
#include "AnimInstanceBase.h"
#include "Stat.h"

UMRangedAttackState::UMRangedAttackState()
{
}

void UMRangedAttackState::Init(AController* pc, FVector atkSize, TSubclassOf<UObject> projectileClass)
{
	controller = pc;
	attackSize = atkSize;
	ProjectileClass = projectileClass;
}

void UMRangedAttackState::Init(AController* pc, FVector atkSize, UAnimMontage* montage, TSubclassOf<UObject> projectileClass)
{
	controller = pc;
	attackSize = atkSize;
	AttackMontages = montage;
	ProjectileClass = projectileClass;
}

void UMRangedAttackState::OnEnterState()
{
	AMonsterAIControllerBase* AMACB = GetAIController();
	ACharacterBase* cb = Cast<ACharacterBase>(AMACB->GetCharacter());
	UAnimInstanceBase* animBase = Cast<UAnimInstanceBase>(cb->GetMesh()->GetAnimInstance());
	UStat* stat = cb->stat;

	cb->WeaponTipSocketName = FName("Fire");
	int32 atkCount = AttackCount++;

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(cb->GetActorLocation(), AMACB->CombatTarget->GetActorLocation());
	cb->SetActorRotation(FRotator(0, Rotation.Yaw, 0));
	//FRotator Rotation = UUtil::LookAt(ACP, AMACB->CombatTarget);
	//ACP->AddActorWorldRotation(FRotator(0, Rotation.Yaw, 0));

// 몽타주 플레이
	animBase->Montage_Play(AttackMontages, stat->GetAtkSpeed());
	animBase->Montage_JumpToSection(FName(FString::FromInt(atkCount)), AttackMontages);
}

void UMRangedAttackState::OnTickState()
{
}

void UMRangedAttackState::OnExitState(ECreatureState post)
{
}

// 애니메이션에서 실행
void UMRangedAttackState::OnRangedAttack()
{
	AMonsterAIControllerBase* macb = GetAIController();
	ACharacterBase* cb = Cast<ACharacterBase>(controller->GetCharacter());

	FVector SocketLocation = FVector::Zero();
	if (ICombatable* combat = Cast<ICombatable>(cb))
	{
		SocketLocation = combat->GetCombatSocketLocation();
	}
	
	FVector target = macb->CombatTarget->GetActorLocation();

	FRotator direction = UKismetMathLibrary::FindLookAtRotation(SocketLocation, target);

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(FQuat::MakeFromRotator(direction));

	// 지연된 스폰

	AProjectile* Projectile = controller->GetWorld()->SpawnActorDeferred<AProjectile>(
		ProjectileClass,
		SpawnTransform,
		controller->GetOwner(),
		controller->GetPawn(),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	// 정보 채우고 스폰
	// 투사체 stat

	Projectile->FinishSpawning(SpawnTransform);
}
