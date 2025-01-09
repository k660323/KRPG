// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "KRPGInputComponent.h"
#include "InputActionValue.h"
#include "CharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Stat.h"
#include "AnimInstanceBase.h"
#include "StateMachineComponent.h"
#include "BaseState.h"
#include "AttackState.h"
#include "JumpState.h"
#include "RollState.h"
#include "KRPGHUD.h"
#include "GameplayTagContainer.h"
#include "KRPGGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WorldItem.h"
#include "InventoryComponent.h"
#include "CountableItem.h"
#include <Define.h>

APlayerControllerBase::APlayerControllerBase()
{
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
		SubSystem->AddMappingContext(InputContext, 0);

	//if (UKRPGInputComponent* KRPGInputComponent = CastChecked<UKRPGInputComponent>(InputComponent))
	//{
	//	if (AKRPGHUD* hud = Cast<AKRPGHUD>(GetHUD()))
	//	{
	//		//KRPGInputComponent->BindAction(ShowStatAction, ETriggerEvent::Started, hud, &AKRPGHUD::ShowStatUI);
	//		//KRPGInputComponent->BindAbilityAction(InputConfig, FKRPGGameplayTags::Get().InputTag_L, this, &APlayerControllerBase::AbilityInputTagPressed, &APlayerControllerBase::AbilityInputTagReleased, &APlayerControllerBase::AbilityInputTagHeld);
	//	}
	//}
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	if (UKRPGInputComponent* KRPGInputComponent = CastChecked<UKRPGInputComponent>(InputComponent))
	{
		KRPGInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerControllerBase::MoveStarted);
		KRPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
		KRPGInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerControllerBase::MoveCompleted);
		KRPGInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Turn);
		KRPGInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::CameraZoom);
	
		KRPGInputComponent->BindAbilityActions(InputConfig, this, &APlayerControllerBase::AbilityInputTagPressed, &APlayerControllerBase::AbilityInputTagReleased, &APlayerControllerBase::AbilityInputTagHeld);
	}
}


void APlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void APlayerControllerBase::MoveStarted(const FInputActionValue& Value)
{
	// 같은 버튼인지 확인
	if (PreMoveInputAxisVector == Value.Get<FVector2D>())
	{
		ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter());

		if (ACP->StateMachineComponent->EState == ECreatureState::Idle || ACP->StateMachineComponent->EState == ECreatureState::Move)
		{
			// 해당 방향으로 회피 모션 작동
			ACP->StateMachineComponent->ChangeState(ECreatureState::Dodge);
		}
	}
}

void APlayerControllerBase::Move(const FInputActionValue& Value)
{
	MoveInputAxisVector = Value.Get<FVector2D>();

	ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter());
	
	if (ACP)
	{
		if (ACP->StateMachineComponent->EState == ECreatureState::Idle)
			ACP->StateMachineComponent->ChangeState(ECreatureState::Move);
	}
}

void APlayerControllerBase::MoveCompleted(const FInputActionValue& Value)
{
	PreMoveInputAxisVector = MoveInputAxisVector;
	
	ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter());
	if (ACP)
	{
		if (ACP->StateMachineComponent->EState == ECreatureState::Move)
			ACP->StateMachineComponent->ChangeState(ECreatureState::Idle);

		// 0.1f초후 이전 무브 벡터 초기화
		GetWorld()->GetTimerManager().ClearTimer(timer);
		GetWorld()->GetTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([this]() { PreMoveInputAxisVector = FVector2D::Zero(); }), 0.1f, false);
	}
}

void APlayerControllerBase::Turn(const FInputActionValue& Value)
{
	TurnInputAxisVector = Value.Get<FVector2D>();

	AddYawInput(TurnInputAxisVector.X);
	AddPitchInput(-TurnInputAxisVector.Y);
}

void APlayerControllerBase::CameraZoom(const FInputActionValue& Value)
{
	float zoom = Value.Get<float>();

	ACharacterPlayer* base = CastChecked<ACharacterPlayer>(GetCharacter());
	
	float armLength = base->GetSpringArm().Get()->TargetArmLength;
	float sum = armLength + zoom * 50.f;
	sum = FMath::Clamp(sum, 300.f, 1000.f);
	float LerpValue = UKismetMathLibrary::Lerp(armLength, sum, 0.5f);
	base->GetSpringArm().Get()->TargetArmLength = LerpValue;
}

void APlayerControllerBase::Jump()
{
	if (ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter()))
	{
		if (TObjectPtr<UJumpState> atk = CastChecked<UJumpState>(ACP->StateMachineComponent->GetState(ECreatureState::Jump)))
		{
			ACP->StateMachineComponent->ChangeState(ECreatureState::Jump);
		}
	}
}

void APlayerControllerBase::StopJumping()
{
	GetCharacter()->StopJumping();
}

void APlayerControllerBase::Attack()
{
	if (TObjectPtr<ACharacterPlayer> acp = CastChecked<ACharacterPlayer>(GetCharacter()))
	{
		if (TObjectPtr<UAttackState> atk = CastChecked<UAttackState>(acp->StateMachineComponent->GetState(ECreatureState::Attack)))
		{
			if (acp->StateMachineComponent->EState == ECreatureState::Idle || acp->StateMachineComponent->EState == ECreatureState::Move)
			{
				if (!atk->GetIsAttacking())
				{
					atk->SetIsAttacking(true);
					acp->StateMachineComponent->ChangeState(ECreatureState::Attack);
				}
			}
			else if (acp->StateMachineComponent->EState == ECreatureState::Attack)
			{
				atk->SetSaveAttack(true);
			}
		}
	}
}

void APlayerControllerBase::Roll()
{
	if (ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter()))
	{
		if (TObjectPtr<URollState> roll = CastChecked<URollState>(ACP->StateMachineComponent->GetState(ECreatureState::Roll)))
		{
			if (ACP->StateMachineComponent->EState == ECreatureState::Idle || ACP->StateMachineComponent->EState == ECreatureState::Move)
				ACP->StateMachineComponent->ChangeState(ECreatureState::Roll);
		}
	}
}

void APlayerControllerBase::ItemSearch()
{
	FHitResult HitResult;

	bool bSuccess = UKismetSystemLibrary::SphereTraceSingle(this,
		GetCharacter()->GetActorLocation(),
		GetCharacter()->GetActorLocation(),
		50.f,
		ETraceTypeQuery::TraceTypeQuery4,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		OUT HitResult,
		true,
		FLinearColor::Yellow,
		FLinearColor::Blue,
		1.f
	);

	if (!bSuccess)
		return;

	AWorldItem* worldItem = Cast<AWorldItem>(HitResult.GetActor());
	if (worldItem == nullptr || worldItem->item == nullptr)
		return;

	int count = 1;
	if (UCountableItem* countableItem = Cast<UCountableItem>(worldItem->item))
		count = countableItem->Amount;

	ACharacterPlayer* cp = Cast<ACharacterPlayer>(GetCharacter());
	if (cp == nullptr)
		return;

	UInventoryComponent* inventory = cp->InventoryComponent;
	if (inventory == nullptr)
		return;

	int32 result = inventory->AddItem(worldItem->item);
	if (result == 0)
		worldItem->Destroy();
}

void APlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_LCtrl))
	{
		Roll();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_SpaceBar))
	{
		Jump();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_LMB))
	{
		Attack();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_L))
	{
		AKRPGHUD* hud = Cast<AKRPGHUD>(GetHUD());
		hud->ShowStatUI();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_I))
	{
		AKRPGHUD* hud = Cast<AKRPGHUD>(GetHUD());
		hud->ShowInventory();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_O))
	{
		AKRPGHUD* hud = Cast<AKRPGHUD>(GetHUD());
		hud->ShowEquipmentWindow();
	}
	else if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_C))
	{
		// 아이템 줍기
		ItemSearch();
	}
	else
	{
		ACharacterPlayer* ACP = Cast<ACharacterPlayer>(GetCharacter());
		ACP->StateMachineComponent->ChangeSkillState(InputTag);
	}
}

void APlayerControllerBase::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FKRPGGameplayTags::Get().InputTag_SpaceBar))
	{
		StopJumping();
	}
}

void APlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
}
