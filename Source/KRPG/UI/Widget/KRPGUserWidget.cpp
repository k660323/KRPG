// Fill out your copyright notice in the Description page of Project Settings.


#include "KRPGUserWidget.h"

void UKRPGUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
