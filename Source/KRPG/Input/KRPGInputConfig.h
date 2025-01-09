// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "KRPGInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FKRPGInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class KRPG_API UKRPGInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FKRPGInputAction> AbilityInputActions;
};
