// Fill out your copyright notice in the Description page of Project Settings.


#include "KRPGHUD.h"
#include "KRPGUserWidget.h"
#include "PlayerControllerBase.h"
#include "CharacterBase.h"

void AKRPGHUD::BeginPlay()
{
	Super::BeginPlay();
}

AKRPGHUD::AKRPGHUD()
{
	
}

void AKRPGHUD::ShowStatUI()
{
	if (StatWidget->IsInViewport())
	{
		GetOwningPlayerController()->SetShowMouseCursor(false);
		StatWidget->RemoveFromParent();
	}
	else
	{
		GetOwningPlayerController()->SetShowMouseCursor(true);
		StatWidget->AddToViewport();
	}
}

void AKRPGHUD::ShowInventory()
{
	if (InventoryWidget->IsInViewport())
	{
		GetOwningPlayerController()->SetShowMouseCursor(false);
		InventoryWidget->RemoveFromParent();
	}
	else
	{
		GetOwningPlayerController()->SetShowMouseCursor(true);
		InventoryWidget->AddToViewport();
	}
}

void AKRPGHUD::ShowEquipmentWindow()
{
	if (EquipmentWindowWidget->IsInViewport())
	{
		GetOwningPlayerController()->SetShowMouseCursor(false);
		EquipmentWindowWidget->RemoveFromParent();
	}
	else
	{
		GetOwningPlayerController()->SetShowMouseCursor(true);
		EquipmentWindowWidget->AddToViewport();
	}
}


void AKRPGHUD::InitOverlay(APlayerControllerBase* PCB)
{
	check(OverlayWidgetClass);
	check(StatWidgetClass);
	check(InventoryWidgetClass);
	check(EquipmentWindowWidgetClass);

	OverlayWidget = CreateWidget<UKRPGUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	StatWidget = CreateWidget<UKRPGUserWidget>(GetWorld(), StatWidgetClass);

	InventoryWidget = CreateWidget<UKRPGUserWidget>(GetWorld(), InventoryWidgetClass);

	EquipmentWindowWidget = CreateWidget<UKRPGUserWidget>(GetWorld(), EquipmentWindowWidgetClass);

	OverlayWidget->SetWidgetController(PCB->GetCharacter());
	StatWidget->SetWidgetController(PCB->GetCharacter());
	InventoryWidget->SetWidgetController(PCB->GetCharacter());
	EquipmentWindowWidget->SetWidgetController(PCB->GetCharacter());
}
