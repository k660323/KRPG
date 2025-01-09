// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayer.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "PlayerControllerBase.h"
#include "Stat.h"
#include "StateMachineComponent.h"
#include "KRPGHUD.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "JumpState.h"
#include "KRPGHUD.h"
#include "InventoryComponent.h"
#include "KGameInstance.h"
#include "EquipmentComponent.h"

ACharacterPlayer::ACharacterPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 450.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
}

void ACharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Init();
}

void ACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	Init();
}

void ACharacterPlayer::Init()
{	
	if (APlayerControllerBase* pcb = Cast<APlayerControllerBase>(GetController()))
	{
		if (AKRPGHUD* KRPGHUD = Cast<AKRPGHUD>(pcb->GetHUD()))
		{
			KRPGHUD->InitOverlay(pcb);
		}
	}

	InitStat();
}

bool ACharacterPlayer::InitStat(int index)
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

void ACharacterPlayer::AllocatedMachine()
{
	APlayerControllerBase* acb = Cast<APlayerControllerBase>(GetController());
	TObjectPtr<UBaseState> state = NewObject<UIdleState>();
	state->Init(acb);
	StateMachineComponent->InitState(ECreatureState::Idle, state);

	state = NewObject<UMoveState>();
	state->Init(acb);
	StateMachineComponent->AddState(ECreatureState::Move, state);

	state = NewObject<UAttackState>();
	state->Init(acb, FVector(50.f, 50.f, 85.f));
	StateMachineComponent->AddState(ECreatureState::Attack, state);

	state = NewObject<UJumpState>();
	state->Init(acb);
	StateMachineComponent->AddState(ECreatureState::Jump, state);
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 멀티가면 수정
	UKGameInstance* KGameInstance = Cast<UKGameInstance>(GetGameInstance());
	KGameInstance->MyPlayer = this;
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StateMachineComponent != nullptr)
		StateMachineComponent->TickState();
}

TObjectPtr<USpringArmComponent> ACharacterPlayer::GetSpringArm()
{
	return SpringArm;
}

bool ACharacterPlayer::LevelUp()
{
	return InitStat(stat->GetLevel() + 1);
}


