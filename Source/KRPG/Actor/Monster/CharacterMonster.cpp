// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMonster.h"
#include "MonsterAIControllerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "KRPGUserWidget.h"
#include "Stat.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "MIdleState.h"
#include "MDieState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

ACharacterMonster::ACharacterMonster()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	//GetMesh()->SetGenerateOverlapEvents(true);

	NickName = CreateDefaultSubobject<UWidgetComponent>("NickName");
	NickName->SetupAttachment(GetRootComponent());

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ACharacterMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Init();
}

void ACharacterMonster::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	Init();
}

void ACharacterMonster::Init()
{
	InitStat(type);
	InitAIController();
	InitPawnSensing();
}

bool ACharacterMonster::InitStat(ECreatureMonster _InitType)
{
	// 설정 안하면 기본값
	JumpMaxCount = 1;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.0f, 0.f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;

	stat.Get()->SetMaxHp(100);
	stat.Get()->SetCurHp(100);
	stat.Get()->SetMaxMp(50);
	stat.Get()->SetCurMp(50);

	return true;
}

void ACharacterMonster::InitAIController()
{
	// 설정 안하면 기본값
	AMonsterAIControllerBase* macb = Cast<AMonsterAIControllerBase>(GetController());
	macb->SpawnPos = GetActorLocation();
	macb->MaxChaseDistance = 3000.f;
	macb->atkRadius = 100.f;
	macb->PatrolRadius = 500.f;
}

void ACharacterMonster::InitPawnSensing()
{
	// 설정 안하면 기본값
	pawnSensing->SetPeripheralVisionAngle(45.f);
	pawnSensing->HearingThreshold = 1300.f;
	pawnSensing->SightRadius = 1500.f;

	pawnSensing->SetComponentTickEnabled(true);
}

void ACharacterMonster::AllocatedMachine()
{
	// 설정 안하면 기본값
	AMonsterAIControllerBase* macb = Cast<AMonsterAIControllerBase>(GetController());
	
	TObjectPtr<UBaseState> state = NewObject<UMIdleState>();
	state->Init(macb);
	StateMachineComponent->InitState(ECreatureState::Idle, state);

	state = NewObject<UMDieState>();
	state->Init(macb, nullptr);
	StateMachineComponent->AddState(ECreatureState::Die, state);
}

void ACharacterMonster::BeginPlay()
{
	Super::BeginPlay();

	if (UKRPGUserWidget* RPGUserWidget = Cast< UKRPGUserWidget>(NickName->GetUserWidgetObject()))
	{
		RPGUserWidget->SetWidgetController(this);
	}

	if (UKRPGUserWidget* RPGUserWidget = Cast< UKRPGUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		RPGUserWidget->SetWidgetController(this);

		stat.Get()->OnCurHpChanged.Broadcast(stat.Get()->GetCurHp());
		stat.Get()->OnMaxHpChanged.Broadcast(stat.Get()->GetMaxHp());
	}

}

void ACharacterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StateMachineComponent != nullptr)
		StateMachineComponent->TickState();
}
