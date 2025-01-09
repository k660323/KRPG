// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ItemSlotWidget.h"
#include "InventoryWidget.h"

UItemSlotWidget::UItemSlotWidget() : _HighlightAlpha(0.5f), _HighlightFadeDuration(0.2f), _CurrentHLAlpha(0.0f), _IsAccessibleSlot(true), _IsAccessibleItem(true), _InaccessibleSlotColor(0.2f,0.2f,0.2f,0.5f), _InaccessibleIconColor(0.5f,0.5f,0.5f,0.5f)
{
}

void UItemSlotWidget::SetInventoryWidgetReference(UInventoryWidget* _InventoryWidget)
{
	InventoryWidget = _InventoryWidget;
}


