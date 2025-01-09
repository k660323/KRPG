// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include <Define.h>
#include "CharacterMonster.generated.h"


class UWidgetComponent;
/**
 * 
 */
UCLASS()
class KRPG_API ACharacterMonster : public ACharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		AActor* Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWidgetComponent> NickName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWidgetComponent> HealthBar;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Type", meta = (AllowPrivateAccess = "true"))
		ECreatureMonster type;

public:
	ACharacterMonster();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Init() override;
	virtual bool InitStat(ECreatureMonster _InitType = ECreatureMonster::None);
	virtual void InitAIController();
	virtual void InitPawnSensing() override;
	virtual void AllocatedMachine() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
