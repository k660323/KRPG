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
	// ���� ������ ����
	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	int32 Amount;

protected:
	virtual UCountableItem* Clone(int _amount);

public:
	UCountableItem();

	UCountableItemData* GetItemData();

	void SetItemData(UCountableItemData& data, int32 _amount = 1);
	
	// �ϳ��� ������ ���� �� �ִ� �ִ� ���� (�⺻ 99)
	UFUNCTION(BlueprintCallable)
	int32 MaxAmount();

	// ������ ���� á���� ���� �ִ� ���� �̻� �ϰ�� true
	UFUNCTION(BlueprintCallable)
	bool IsMax();

	// ������ ������ ����
	UFUNCTION(BlueprintCallable)
	bool IsEmpty();

	// ���� ����(Clamp�� ����)
	UFUNCTION(BlueprintCallable)
	void SetAmount(int32 _amount);

	// ���� �߰� �� �ִ�ġ �ʰ��� ��ȯ(�ʰ��� ���� ��� 0)
	UFUNCTION(BlueprintCallable)
	int32 AddAmountAndGetExcess(int32 _amount);

	// ������ ������ ����
	UFUNCTION(BlueprintCallable)
	UCountableItem* SeperateAndClone(int _amount);
};
