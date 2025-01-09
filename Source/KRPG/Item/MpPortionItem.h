// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PortionItem.h"
#include "MpPortionItem.generated.h"

/**
 * 
 */
UCLASS()
class KRPG_API UMpPortionItem : public UPortionItem
{
	GENERATED_BODY()
protected:
	virtual UCountableItem* Clone(int _amount) override;

public:
	UMpPortionItem();

	virtual bool Use() override;
};
