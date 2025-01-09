// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "PlayerControllerBase.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharacterPlayer;
class UKRPGInputConfig;

using namespace std;
/**
 * 
 */
UCLASS()
class KRPG_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerControllerBase();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;

	void MoveStarted(const struct FInputActionValue& Value);
	void Move(const struct FInputActionValue& Value);
	void MoveCompleted(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);
	void CameraZoom(const struct FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void Attack();
	void Roll();
	void ItemSearch();

private:
	FTimerHandle timer;

public:
	UPROPERTY(EditAnywhere, Category = "InputAxis");
	FVector2D PreMoveInputAxisVector;

	UPROPERTY(EditAnywhere, Category = "InputAxis");
	FVector2D MoveInputAxisVector;

	UPROPERTY(EditAnywhere, Category = "InputAxis");
	FVector2D TurnInputAxisVector;

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		TObjectPtr<UKRPGInputConfig> InputConfig;

public:
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
