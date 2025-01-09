// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurHpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurMpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpCountChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhysicalAttackChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicAttackChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhysicalDefenceChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicDefenceChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSTRChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnINTChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDEXChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLUKChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurStatCountChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpRecoveryChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMpRecoveryChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExpChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxExpChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAtkSpeedChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCriticalChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpZVelocityChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAirControlChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxWalkSpeedChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinWalkSpeedChangedSignature, float, NewValue);

// Additive
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveLevelChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMaxHpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMaxMpChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveJumpCountChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditivePhysicalAttackChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMagicAttackChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditivePhysicalDefenceChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMagicDefenceChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveSTRChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveINTChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveDEXChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveLUKChangedSignature, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveHpRecoveryChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMpRecoveryChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveAtkSpeedChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveCriticalChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveRotationChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveJumpZVelocityChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveAirControlChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMaxWalkSpeedChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdditiveMinWalkSpeedChangedSignature, float, NewValue);

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRPG_API UStat : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 CurHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 CurMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 JumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 PhysicalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 MagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 PhysicalDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 MagicDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 LUK;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 CurStatCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float HpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float MpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float AtkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float Critical;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float JumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AirControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float MinAnalogWalkSpeed;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveLevel;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
	//	int32 AdditiveCurHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveMaxHp;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
	//	int32 AdditiveCurMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveMaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveJumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditivePhysicalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveMagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditivePhysicalDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveMagicDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveSTR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveINT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveDEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		int32 AdditiveLUK;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveHpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveMpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveAtkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveCritical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveCharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveCharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveJumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveCharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveAirControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveCharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdditiveCharacterMovementStat", meta = (AllowPrivateAccess = "true"))
		float AdditiveMinAnalogWalkSpeed;

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnLevelChangedSignature OnLevelChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnCurHpChangedSignature OnCurHpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMaxHpChangedSignature OnMaxHpChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnCurMpChangedSignature OnCurMpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMaxMpChangedSignature OnMaxMpChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnJumpCountChangedSignature OnJumpCountChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnPhysicalAttackChangedSignature OnPhysicalAttackChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMagicAttackChangedSignature OnMagicAttackChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnPhysicalDefenceChangedSignature OnPhysicalDefenceChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMagicDefenceChangedSignature OnMagicDefenceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnSTRChangedSignature OnSTRChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnINTChangedSignature OnINTChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnDEXChangedSignature OnDEXChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnLUKChangedSignature OnLUKChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnCurStatCountChangedSignature OnCurStatCountChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnHpRecoveryChangedSignature OnHpRecoveryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMpRecoveryChangedSignature OnMpRecoveryChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnExpChangedSignature OnExpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMaxExpChangedSignature OnMaxExpChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAtkSpeedChangedSignature OnAtkSpeedChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnCriticalChangedSignature OnCriticalChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnRotationChangedSignature OnRotationChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnJumpZVelocityChangedSignature OnJumpZVelocityChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAirControlChangedSignature OnAirControlChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMaxWalkSpeedChangedSignature OnMaxWalkSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnMinWalkSpeedChangedSignature OnMinWalkSpeedChanged;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveLevelChangedSignature OnAdditiveLevelChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMaxHpChangedSignature OnAdditiveMaxHpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMaxMpChangedSignature OnAdditiveMaxMpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveJumpCountChangedSignature OnAdditiveJumpCountChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditivePhysicalAttackChangedSignature OnAdditivePhysicalAttackChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMagicAttackChangedSignature OnAdditiveMagicAttackChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditivePhysicalDefenceChangedSignature OnAdditivePhysicalDefenceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMagicDefenceChangedSignature OnAdditiveMagicDefenceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveSTRChangedSignature OnAdditiveSTRChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveINTChangedSignature OnAdditiveINTChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveDEXChangedSignature OnAdditiveDEXChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveLUKChangedSignature OnAdditiveLUKChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveHpRecoveryChangedSignature OnAdditiveHpRecoveryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMpRecoveryChangedSignature OnAdditiveMpRecoveryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveAtkSpeedChangedSignature OnAdditiveAtkSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveCriticalChangedSignature OnAdditiveCriticalChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveRotationChangedSignature OnAdditiveRotationChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveJumpZVelocityChangedSignature OnAdditiveJumpZVelocityChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveAirControlChangedSignature OnAdditiveAirControlChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMaxWalkSpeedChangedSignature OnAdditiveMaxWalkSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FOnAdditiveMinWalkSpeedChangedSignature OnAdditiveMinWalkSpeedChanged;

	UPROPERTY()
		FTimerHandle hpTimer;
	UPROPERTY()
		FTimerHandle mpTimer;
public:	
	// Sets default values for this component's properties
	UStat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void InitStat(ACharacterBase* Character);
	
	UFUNCTION(BlueprintCallable)
	int32 GetLevel()
	{
		return Level;
	}

	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 Value)
	{
		Level = FMath::Max(0, Value);
		OnLevelChanged.Broadcast(Level);
	}
	
	UFUNCTION(BlueprintCallable)
	int32 GetCurHp()
	{
		return CurHp;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurHp(int32 Value)
	{
		CurHp = FMath::Clamp(Value, 0, MaxHp + AdditiveMaxHp);
		OnCurHpChanged.Broadcast(CurHp);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHp()
	{
		return MaxHp;
	}

	UFUNCTION(BlueprintCallable)
	void SetMaxHp(int32 Value)
	{
		MaxHp = FMath::Max(0, Value);
		OnMaxHpChanged.Broadcast(MaxHp);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurMp()
	{
		return CurMp;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurMp(int32 Value)
	{
		CurMp = FMath::Clamp(Value, 0, MaxMp + AdditiveMaxMp);
		OnCurMpChanged.Broadcast(CurMp);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxMp()
	{
		return MaxMp;
	}

	UFUNCTION(BlueprintCallable)
	void SetMaxMp(int32 Value)
	{
		MaxMp = FMath::Max(0, Value);
		OnMaxMpChanged.Broadcast(MaxMp);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetJumpCount()
	{
		return JumpCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetJumpCount(int Value)
	{
		JumpCount = FMath::Max(0, Value);
		OnJumpCountChanged.Broadcast(JumpCount);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetPhysicalAttack()
	{
		return PhysicalAttack;
	}

	UFUNCTION(BlueprintCallable)
	void SetPhysicalAttack(int Value)
	{
		PhysicalAttack = FMath::Max(0, Value);
		OnPhysicalAttackChanged.Broadcast(PhysicalAttack);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMagicAttack()
	{
		return MagicAttack;
	}

	UFUNCTION(BlueprintCallable)
	void SetMagicAttack(int Value)
	{
		MagicAttack = FMath::Max(0, Value);
		OnMagicAttackChanged.Broadcast(MagicAttack);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetPhysicalDefence()
	{
		return PhysicalDefence;
	}

	UFUNCTION(BlueprintCallable)
	void SetPhysicalDefence(int Value)
	{
		PhysicalDefence = FMath::Max(0, Value);
		OnPhysicalDefenceChanged.Broadcast(PhysicalDefence);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMagicDefence()
	{
		return MagicDefence;
	}

	UFUNCTION(BlueprintCallable)
	void SetMagicDefence(int Value)
	{
		MagicDefence = FMath::Max(0, Value);
		OnMagicDefenceChanged.Broadcast(MagicDefence);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetSTR()
	{
		return STR;
	}

	UFUNCTION(BlueprintCallable)
	void SetSTR(int Value)
	{
		STR = FMath::Max(0, Value);
		OnSTRChanged.Broadcast(STR);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetINT()
	{
		return INT;
	}

	UFUNCTION(BlueprintCallable)
	void SetINT(int Value)
	{
		INT = FMath::Max(0, Value);
		OnINTChanged.Broadcast(INT);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetDEX()
	{
		return DEX;
	}

	UFUNCTION(BlueprintCallable)
	void SetDEX(int Value)
	{
		DEX = FMath::Max(0, Value);
		OnDEXChanged.Broadcast(DEX);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetLUK()
	{
		return LUK;
	}

	UFUNCTION(BlueprintCallable)
	void SetLUK(int Value)
	{
		LUK = FMath::Max(0, Value);
		OnLUKChanged.Broadcast(LUK);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurStatCount()
	{
		return CurStatCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurStatCount(int Value)
	{
		CurStatCount = FMath::Max(0, Value);
		OnCurStatCountChanged.Broadcast(CurStatCount);
	}

	UFUNCTION(BlueprintCallable)
	float GetHpRecovery()
	{
		return HpRecovery;
	}

	UFUNCTION(BlueprintCallable)
	void SetHpRecovery(float Value)
	{
		HpRecovery = FMath::Max(0, Value);
		OnHpRecoveryChanged.Broadcast(HpRecovery);
	}

	UFUNCTION(BlueprintCallable)
	float GetMpRecovery()
	{
		return MpRecovery;
	}

	UFUNCTION(BlueprintCallable)
	void SetMpRecovery(float Value)
	{
		MpRecovery = FMath::Max(0, Value);
		OnMpRecoveryChanged.Broadcast(MpRecovery);
	}

	UFUNCTION(BlueprintCallable)
	float GetExp()
	{
		return Exp;
	}

	UFUNCTION(BlueprintCallable)
	void SetExp(float Value)
	{
		Exp = FMath::Max(0, Value);
		OnExpChanged.Broadcast(Exp);
	}

	UFUNCTION(BlueprintCallable)
	float GetMaxExp()
	{
		return MaxExp;
	}

	UFUNCTION(BlueprintCallable)
	void SetMaxExp(float Value)
	{
		MaxExp = FMath::Max(0, Value);
		OnMaxExpChanged.Broadcast(MaxExp);
	}

	UFUNCTION(BlueprintCallable)
	float GetAtkSpeed()
	{
		return AtkSpeed;
	}

	UFUNCTION(BlueprintCallable)
	void SetAtkSpeed(float Value)
	{
		AtkSpeed = FMath::Max(0, Value);
		OnAtkSpeedChanged.Broadcast(AtkSpeed);
	}

	UFUNCTION(BlueprintCallable)
	float GetCritical()
	{
		return Critical;
	}

	UFUNCTION(BlueprintCallable)
	void SetCritical(float Value)
	{
		Critical = FMath::Max(0, Value);
		OnCriticalChanged.Broadcast(Critical);
	}

	UFUNCTION(BlueprintCallable)
	float GetRotationRate()
	{
		return RotationRate;
	}

	UFUNCTION(BlueprintCallable)
	void SetRotationRate(float Value)
	{
		RotationRate = Value;
		OnRotationChanged.Broadcast(RotationRate);
	}

	UFUNCTION(BlueprintCallable)
	float GetJumpZVelocity()
	{
		return JumpZVelocity;
	}

	UFUNCTION(BlueprintCallable)
	void SetJumpZVelocity(float Value)
	{
		JumpZVelocity = Value;
		OnJumpZVelocityChanged.Broadcast(JumpZVelocity);
	}

	UFUNCTION(BlueprintCallable)
	float GetAirControl()
	{
		return AirControl;
	}

	UFUNCTION(BlueprintCallable)
	void SetAirControl(float Value)
	{
		AirControl = Value;
		OnAirControlChanged.Broadcast(AirControl);
	}

	UFUNCTION(BlueprintCallable)
	float GetMaxWalkSpeed()
	{
		return MaxWalkSpeed;
	}

	UFUNCTION(BlueprintCallable)
	void SetMaxWalkSpeed(float Value)
	{
		MaxWalkSpeed = FMath::Max(0, Value);
		OnMaxWalkSpeedChanged.Broadcast(MaxWalkSpeed);
	}

	UFUNCTION(BlueprintCallable)
	float GetMinAnalogWalkSpeed()
	{
		return MinAnalogWalkSpeed;
	}

	UFUNCTION(BlueprintCallable)
	void SetMinAnalogWalkSpeed(float Value)
	{
		MinAnalogWalkSpeed = FMath::Max(0, Value);
		OnMinWalkSpeedChanged.Broadcast(MinAnalogWalkSpeed);
	}

public:
	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveLevel()
	{
		return AdditiveLevel;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveLevel(int32 Value)
	{
		AdditiveLevel += Value;
		OnAdditiveLevelChanged.Broadcast(Level);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveMaxHp()
	{
		return AdditiveMaxHp;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMaxHp(int32 Value)
	{
		AdditiveMaxHp += Value;
		OnAdditiveMaxHpChanged.Broadcast(AdditiveMaxHp);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveMaxMp()
	{
		return AdditiveMaxMp;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMaxMp(int32 Value)
	{
		AdditiveMaxMp += Value;
		OnAdditiveMaxMpChanged.Broadcast(AdditiveMaxMp);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveJumpCount()
	{
		return AdditiveJumpCount;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveJumpCount(int Value)
	{
		AdditiveJumpCount += Value;
		OnAdditiveJumpCountChanged.Broadcast(AdditiveJumpCount);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditivePhysicalAttack()
	{
		return AdditivePhysicalAttack;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditivePhysicalAttack(int Value)
	{
		AdditivePhysicalAttack += Value;
		OnAdditivePhysicalAttackChanged.Broadcast(AdditivePhysicalAttack);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveMagicAttack()
	{
		return AdditiveMagicAttack;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMagicAttack(int Value)
	{
		AdditiveMagicAttack += Value;
		OnAdditiveMagicAttackChanged.Broadcast(AdditiveMagicAttack);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditivePhysicalDefence()
	{
		return AdditivePhysicalDefence;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditivePhysicalDefence(int Value)
	{
		AdditivePhysicalDefence += Value;
		OnAdditivePhysicalDefenceChanged.Broadcast(AdditivePhysicalDefence);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveMagicDefence()
	{
		return AdditiveMagicDefence;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMagicDefence(int Value)
	{
		AdditiveMagicDefence += Value;
		OnAdditiveMagicDefenceChanged.Broadcast(AdditiveMagicDefence);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveSTR()
	{
		return AdditiveSTR;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveSTR(int Value)
	{
		AdditiveSTR += Value;
		OnAdditiveSTRChanged.Broadcast(AdditiveSTR);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveINT()
	{
		return AdditiveINT;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveINT(int Value)
	{
		AdditiveINT += Value;
		OnAdditiveINTChanged.Broadcast(AdditiveINT);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveDEX()
	{
		return AdditiveDEX;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveDEX(int Value)
	{
		AdditiveDEX += Value;
		OnAdditiveDEXChanged.Broadcast(AdditiveDEX);
	}

	UFUNCTION(BlueprintCallable)
		int32 GetAdditiveLUK()
	{
		return AdditiveLUK;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveLUK(int Value)
	{
		AdditiveLUK += Value;
		OnAdditiveLUKChanged.Broadcast(AdditiveLUK);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveHpRecovery()
	{
		return AdditiveHpRecovery;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveHpRecovery(float Value)
	{
		AdditiveHpRecovery += Value;
		OnAdditiveHpRecoveryChanged.Broadcast(AdditiveHpRecovery);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveMpRecovery()
	{
		return AdditiveMpRecovery;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMpRecovery(float Value)
	{
		AdditiveMpRecovery += Value;
		OnAdditiveMpRecoveryChanged.Broadcast(AdditiveMpRecovery);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveAtkSpeed()
	{
		return AdditiveAtkSpeed;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveAtkSpeed(float Value)
	{
		AdditiveAtkSpeed += Value;
		OnAdditiveAtkSpeedChanged.Broadcast(AdditiveAtkSpeed);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveCritical()
	{
		return AdditiveCritical;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveCritical(float Value)
	{
		AdditiveCritical += Value;
		OnAdditiveCriticalChanged.Broadcast(AdditiveCritical);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveRotationRate()
	{
		return AdditiveRotationRate;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveRotationRate(float Value)
	{
		AdditiveRotationRate += Value;
		OnAdditiveRotationChanged.Broadcast(AdditiveRotationRate);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveJumpZVelocity()
	{
		return AdditiveJumpZVelocity;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveJumpZVelocity(float Value)
	{
		AdditiveJumpZVelocity += Value;
		OnAdditiveJumpZVelocityChanged.Broadcast(AdditiveJumpZVelocity);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveAirControl()
	{
		return AdditiveAirControl;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveAirControl(float Value)
	{
		AdditiveAirControl += Value;
		OnAdditiveAirControlChanged.Broadcast(AdditiveAirControl);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveMaxWalkSpeed()
	{
		return AdditiveMaxWalkSpeed;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMaxWalkSpeed(float Value)
	{
		AdditiveMaxWalkSpeed += Value;
		OnAdditiveMaxWalkSpeedChanged.Broadcast(AdditiveMaxWalkSpeed);
	}

	UFUNCTION(BlueprintCallable)
		float GetAdditiveMinAnalogWalkSpeed()
	{
		return AdditiveMinAnalogWalkSpeed;
	}

	UFUNCTION(BlueprintCallable)
		void SetAdditiveMinAnalogWalkSpeed(float Value)
	{
		AdditiveMinAnalogWalkSpeed += Value;
		OnAdditiveMinWalkSpeedChanged.Broadcast(AdditiveMinAnalogWalkSpeed);
	}
public:

	UFUNCTION(BlueprintCallable)
		void OnAttacked(UStat* Attacker,EDamageType DamageType, float attackDamage);

	UFUNCTION(BlueprintCallable)
		void OnAttackedCTS(int32 AttackerId, float attackDamage);

	UFUNCTION(BlueprintCallable)
		void ExpCalculation(float addExp);

	UFUNCTION(BlueprintCallable)
		void SetPointToStat(EFStat type)
	{
		if (CurStatCount <= 0)
			return;

		switch (type)
		{
		case EFStat::STR:  // STR
			SetSTR(GetSTR() + 1);
			break;
		case EFStat::INT : // INT
			SetINT(GetINT() + 1);
			break;
		case EFStat::DEX : // DEX
			SetDEX(GetDEX() + 1);
			break;
		case EFStat::LUK : // LUK
			SetLUK(GetLUK() + 1);
			break;
		}
		SetCurStatCount(GetCurStatCount() - 1);
	}

	UFUNCTION(BlueprintCallable)
		void HpRecoveryNatural(int value);

	UFUNCTION(BlueprintCallable)
		void MpRecoveryNatural(int value);
};
