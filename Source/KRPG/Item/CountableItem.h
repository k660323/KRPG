// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "ItemDataTable.h"
#include "CountableItem.generated.h"

class UItemData;
class UCountableItemData;
/**
 * 
 */
UCLASS()
class KRPG_API UCountableItem : public UItem
{
	GENERATED_BODY()

public:
	// 현재 아이템 개수
	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	int32 Amount;

protected:
	virtual UCountableItem* Clone(int _amount);

public:
	UCountableItem();

	UCountableItemData* GetItemData();

	void SetItemData(UCountableItemData& data, int32 _amount = 1);
	
	// 하나의 슬롯이 가질 수 있는 최대 개수 (기본 99)
	UFUNCTION(BlueprintCallable)
	int32 MaxAmount();

	// 수량이 가득 찼는지 여부 최대 개수 이상 일경우 true
	UFUNCTION(BlueprintCallable)
	bool IsMax();

	// 개수가 없는지 여부
	UFUNCTION(BlueprintCallable)
	bool IsEmpty();

	// 개수 지정(Clamp로 제한)
	UFUNCTION(BlueprintCallable)
	void SetAmount(int32 _amount);

	// 개수 추가 및 최대치 초과량 반환(초과량 없을 경우 0)
	UFUNCTION(BlueprintCallable)
	int32 AddAmountAndGetExcess(int32 _amount);

	// 개수를 나누어 복제
	UFUNCTION(BlueprintCallable)
	UCountableItem* SeperateAndClone(int _amount);
};
