// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KRPGUserWidget.h"
#include "Define.h"
#include "EquipItemSlotWidget.generated.h"

class UEquipmentWindowWidget;
/**
 * 
 */
UCLASS()
class KRPG_API UEquipItemSlotWidget : public UKRPGUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "EquipType", meta = (AllowPrivateAccess = "true"))
		EEquipType type;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "EquipType", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UEquipmentWindowWidget> EquipmentWindowWidget;

public:
	UEquipItemSlotWidget();

	UFUNCTION(BlueprintCallable)
		void InitEquipItemSlotWidget(UEquipmentWindowWidget* _EquipmentWindowWidget, EEquipType _type);
};
