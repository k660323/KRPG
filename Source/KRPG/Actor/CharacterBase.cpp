// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Stat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachineComponent.h"
#include "Perception/PawnSensingComponent.h"
#include <Define.h>

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StateMachineComponent = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachineComponent"));
	
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	pawnSensing->SetComponentTickEnabled(false);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AllocatedMachine();
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::Init()
{
	// ���� ���ϸ� �⺻��
	InitPawnSensing();
}

void ACharacterBase::InitPawnSensing()
{
	// ���� ���ϸ� �⺻��

}

void ACharacterBase::AllocatedMachine()
{
	// ���� ���ϸ� �⺻��

}

FVector ACharacterBase::GetCombatSocketLocation()
{
	// ���� �𵨸� ��ü�� �������
	FVector Center = GetMesh()->GetSocketLocation(WeaponTipSocketName);
	return Center;
}

void ACharacterBase::BindCharacterMovement(float Value)
{ 
	GetCharacterMovement()->RotationRate = FRotator(0.f, Value, 0.f); 
};
void ACharacterBase::BindJumpZVelocity(float Value) { GetCharacterMovement()->JumpZVelocity = Value; };
void ACharacterBase::BindAirControl(float Value) { GetCharacterMovement()->AirControl = Value; };
void ACharacterBase::BindMaxWalkSpeed(float Value) { GetCharacterMovement()->MaxWalkSpeed = Value; };
void ACharacterBase::BindMinAnalogWalkSpeed(float Value) { GetCharacterMovement()->MinAnalogWalkSpeed = Value; };
void ACharacterBase::BindJumpMaxCount(int32 Value) { JumpMaxCount = Value; };

