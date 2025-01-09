// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KRPGUserWidget.h"
#include "InventoryWidget.generated.h"

class UItemSlotWidget;
class UInventoryComponent;
class UDragDropOperation;
/**
 * 
 */
UCLASS()
class KRPG_API UInventoryWidget : public UKRPGUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UItemSlotWidget*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float _contentAreaPadding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 _horizontalSlotCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 _verticalSlotCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float _slotPadding ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float _slotSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> Inventory;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemSlotWidget> slotClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UDragDropOperation> dropItem;
public:
	UInventoryWidget();

	UFUNCTION()
	void SetInventoryReference(UInventoryComponent* _Inventory);

	UFUNCTION(BlueprintImplementableEvent)
		void SetAccessibleSlotRangeAllEvt(int32 capacity);

	UFUNCTION(BlueprintImplementableEvent)
		void SetItemIconEvt(int32 index, UTexture2D* iconTexture);

	UFUNCTION(BlueprintImplementableEvent)
		void SetItemAmountTextEvt(int32 index, int32 amount);

	UFUNCTION(BlueprintImplementableEvent)
		void HideItemAmountTextEvt(int32 index);

	UFUNCTION(BlueprintImplementableEvent)
		void RemoveSlotEvt(int32 index);
};
