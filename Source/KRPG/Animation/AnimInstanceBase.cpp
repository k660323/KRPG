// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "StateMachineComponent.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacterBase>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
		StateMachineComponent = Character->StateMachineComponent;
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent == nullptr)
		return;

	// 변수값 매프레임마다 갱신
	Speed = Character->GetVelocity().Length();
	IsInAir = MovementComponent->IsFalling();

	// 움직일때 바라보는방향, 현재 캐릭터 위치 방향 차이를 구해 값 저장
	{
		const FRotator AimRotaion = Character->GetBaseAimRotation();
		const FRotator ActorRotaion = Character->GetActorRotation();
		const FRotator DiffRotaion = UKismetMathLibrary::NormalizedDeltaRotator(AimRotaion, ActorRotaion);
		Pitch = DiffRotaion.Pitch;
		Yaw = DiffRotaion.Yaw;
		Roll = DiffRotaion.Roll;
	}

	// 회전 보간
	{
		const FRotator CurrentRotation = Character->GetActorRotation();
		const FRotator DiffRotaion = UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, CurrentRotation);
		float Target = DiffRotaion.Yaw / DeltaSeconds / 7.f;
		YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, Target, DeltaSeconds, 6.f);
		RotationLastTick = CurrentRotation;
	}

	IsAccelerating = MovementComponent->Velocity.Length() > 0;


	if (StateMachineComponent == nullptr)
		return;

	CurState = StateMachineComponent->EState;
}
