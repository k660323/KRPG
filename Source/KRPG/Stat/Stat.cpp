// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "CharacterBase.h"
#include "StateMachineComponent.h"
#include "Components/CapsuleComponent.h"
#include "CharacterPlayer.h"
#include "BaseState.h"
#include "MonsterAIControllerBase.h"
#include <Define.h>

// Sets default values for this component's properties
UStat::UStat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnCurHpChanged.AddUniqueDynamic(this, &UStat::HpRecoveryNatural);
	OnCurMpChanged.AddUniqueDynamic(this, &UStat::MpRecoveryNatural);
}

void UStat::InitializeComponent()
{
	Super::InitializeComponent();

}

void UStat::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(hpTimer);
	GetWorld()->GetTimerManager().ClearTimer(mpTimer);
}


// Called every frame
void UStat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStat::InitStat(ACharacterBase* Character)
{
	// 오버드라이브 안할시 기본 적용 값
	if (Character == nullptr)
		return;

	Character->GetCharacterMovement()->bOrientRotationToMovement = true;

	Character->JumpMaxCount = 1;
	Character->GetCharacterMovement()->RotationRate = FRotator(0.f, 500.0f, 0.f);
	Character->GetCharacterMovement()->JumpZVelocity = 500.f;
	Character->GetCharacterMovement()->AirControl = 0.35f;
	Character->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	Character->GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
}

void UStat::OnAttacked(UStat* Attacker, EDamageType DamageType, float attackDamage)
{
	if (GetCurHp() <= 0)
		return;

	ACharacterBase* cb = GetOwner<ACharacterBase>();
	AController* controller = cb->GetController();
	UStateMachineComponent* smc = cb->StateMachineComponent;

	//
	float finalDamage = (DamageType == EDamageType::Physical) ? attackDamage - PhysicalDefence : attackDamage - MagicDefence;
	finalDamage = FMath::Max(0, finalDamage);
	SetCurHp(GetCurHp() - finalDamage);

	if (GetCurHp() > 0)
	{
		if (AMonsterAIControllerBase* mab = Cast<AMonsterAIControllerBase>(controller))
			if (mab->CombatTarget == nullptr)
				mab->CombatTarget = Cast<ACharacterBase>(Attacker->GetOwner());


		if ((smc->EState == ECreatureState::Idle || smc->EState == ECreatureState::Chase) && smc->EState != ECreatureState::Hit)
			if (UBaseState* hitState = smc->GetState(ECreatureState::Hit))
				smc->ChangeState(ECreatureState::Hit);
	}
	else
	{
		//GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
		//GetMesh()->SetGenerateOverlapEvents(true);
		Attacker->ExpCalculation(GetMaxExp());
		cb->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		smc->ChangeState(ECreatureState::Die);
	}
}

void UStat::OnAttackedCTS(int32 AttackerId, float attackDamage)
{
	// 서버 구현할때 쓸거
}

void UStat::ExpCalculation(float addExp)
{
	float total = GetExp() + addExp;

	if (GetMaxExp() <= total)
	{
		float rest = total - GetMaxExp();
		
		if (ACharacterPlayer* player = Cast<ACharacterPlayer>(GetOwner()))
		{
			if (player->LevelUp())
			{
				if (GetMaxExp() <= rest)
					ExpCalculation(rest);
			}
			else
			{
				SetExp(GetMaxExp());
			}		
		}
		else
		{
			SetExp(GetMaxExp());
		}
	}
	else
	{
		SetExp(total);
	}
}

void UStat::HpRecoveryNatural(int value)
{
	bool bTimerActive = GetWorld()->GetTimerManager().IsTimerActive(hpTimer);
	if (!bTimerActive)
	{
		if (CurHp < MaxHp)
		{
			GetWorld()->GetTimerManager().SetTimer(hpTimer,
				FTimerDelegate::CreateLambda([this]()
					{
						SetCurHp(CurHp + HpRecovery + AdditiveHpRecovery);
					})
				, 10.f
				, true);
		}
	}
}

void UStat::MpRecoveryNatural(int value)
{
	bool bTimerActive = GetWorld()->GetTimerManager().IsTimerActive(mpTimer);
	if (!bTimerActive)
	{
		if (CurMp < MaxMp)
		{
			GetWorld()->GetTimerManager().SetTimer(mpTimer,
				FTimerDelegate::CreateLambda([this]()
					{
						SetCurMp(CurMp + MpRecovery + AdditiveMpRecovery);
					})
				, 10.f
				, true);
		}
	}
}