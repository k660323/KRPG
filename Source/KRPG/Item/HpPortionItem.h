// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PortionItem.h"
#include "HpPortionItem.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UHpPortionItem : public UPortionItem
{
	GENERATED_BODY()

protected:
	virtual UCountableItem* Clone(int _amount) override;

public:
	UHpPortionItem();

	virtual bool Use() override;
};
