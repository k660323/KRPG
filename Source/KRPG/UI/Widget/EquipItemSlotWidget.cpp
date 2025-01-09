// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/EquipItemSlotWidget.h"
#include "EquipmentWindowWidget.h"

UEquipItemSlotWidget::UEquipItemSlotWidget()
{
}

void UEquipItemSlotWidget::InitEquipItemSlotWidget(UEquipmentWindowWidget* _EquipmentWindowWidget, EEquipType _type)
{
	EquipmentWindowWidget = _EquipmentWindowWidget;
	type = _type;
}
