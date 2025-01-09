// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include <Define.h>
#include "CharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;
class UEquipmentComponent;
using namespace std;

/**
 * 
 */
UCLASS()
class KRPG_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Type", meta = (AllowPrivateAccess = "true"))
		ECreaturePlayer type;

public:
	// 해당 플레이어 클래스에서 컴포넌트 할당
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInventoryComponent> InventoryComponent;

	// 해당 플레이어 클래스에서 컴포넌트 할당
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UEquipmentComponent> EquipmentComponent;
public:
	ACharacterPlayer();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Init() override;
	virtual bool InitStat(int index = 1);
	virtual void AllocatedMachine() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TObjectPtr<USpringArmComponent> GetSpringArm();

	UFUNCTION()
	bool LevelUp();
};
