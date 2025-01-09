// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KRPGUserWidget.h"
#include "Define.h"
#include "EquipmentWindowWidget.generated.h"

class UEquipmentComponent;
class UEquipItemSlotWidget;
/**
 * 
 */
UCLASS()
class KRPG_API UEquipmentWindowWidget : public UKRPGUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipments", meta = (AllowPrivateAccess = "true"))
		TMap<EEquipType, UEquipItemSlotWidget*> equipItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UEquipmentComponent> EquipmentComponent;

public:
	UFUNCTION()
		void SetEquipmentWindowReference(UEquipmentComponent* _InventoryWidget);

	UFUNCTION(BlueprintImplementableEvent)
		void SetItemIconEvt(EEquipType equipType, UTexture2D* iconTexture);
};
