// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KRPGHUD.generated.h"

class UKRPGUserWidget;
class APlayerControllerBase;
/**
 * 
 */
UCLASS()
class KRPG_API AKRPGHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AKRPGHUD();
	void ShowStatUI();
	void ShowInventory();
	void ShowEquipmentWindow();
	void InitOverlay(APlayerControllerBase* PCB);

public:
	//UPROPERTY()
	//	TObjectPtr<stack<UKRPGUserWidget>> UIs;

	UPROPERTY()
		TObjectPtr<UKRPGUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UKRPGUserWidget> OverlayWidgetClass;

	UPROPERTY()
		TObjectPtr<UKRPGUserWidget> StatWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UKRPGUserWidget> StatWidgetClass;

	UPROPERTY()
		TObjectPtr<UKRPGUserWidget> InventoryWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UKRPGUserWidget> InventoryWidgetClass;

	UPROPERTY()
		TObjectPtr<UKRPGUserWidget> EquipmentWindowWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UKRPGUserWidget> EquipmentWindowWidgetClass;
};
