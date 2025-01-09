// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CountableItem.h"
#include "UseableItem.h"
#include "PortionItem.generated.h"


class UPortionItemData;
/**
 * 
 */
UCLASS()
class KRPG_API UPortionItem : public UCountableItem, public IUseableItem
{
	GENERATED_BODY()
protected:
	virtual UCountableItem* Clone(int _amount) override;

public:
	UPortionItem();

	UPortionItemData* GetItemData();

	void SetItemData(UPortionItemData& data, int32 _amount = 1);
	
	virtual bool Use() override;
};
