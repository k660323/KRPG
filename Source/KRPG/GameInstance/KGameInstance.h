// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UKGameInstance();

	virtual void Init() override;

	UPROPERTY()
	AActor* MyPlayer;
};
