// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/InventoryWidget.h"
#include "ItemSlotWidget.h"

UInventoryWidget::UInventoryWidget() : _contentAreaPadding(10.f), _horizontalSlotCount(5), _verticalSlotCount(8), _slotPadding(5.f), _slotSize(100.f)
{
}

void UInventoryWidget::SetInventoryReference(UInventoryComponent* _Inventory)
{
	Inventory = _Inventory;
}
