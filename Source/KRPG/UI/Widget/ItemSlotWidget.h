// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KRPGUserWidget.h"
#include "ItemSlotWidget.generated.h"


class UInventoryWidget;
/**
 * 
 */
UCLASS()
class KRPG_API UItemSlotWidget : public UKRPGUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		float _HighlightAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		float _HighlightFadeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		float _CurrentHLAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		bool _IsAccessibleSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		bool _IsAccessibleItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		int32 _Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		FColor _InaccessibleSlotColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
		FColor _InaccessibleIconColor;

public:
	UItemSlotWidget();

	UFUNCTION(BlueprintCallable)
	void SetInventoryWidgetReference(UInventoryWidget* _InventoryWidget);

	UFUNCTION(BlueprintImplementableEvent)
	void SetSlotAccessibleStateEvt(bool value);
};
