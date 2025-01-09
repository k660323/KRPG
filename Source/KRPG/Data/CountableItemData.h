// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemData.h"
#include "CountableItemData.generated.h"


class UCountableItem;
/**
 * 
 */
UCLASS()
class KRPG_API UCountableItemData : public UItemData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountableItem")
		int32 MaxAmount;

public:
	UCountableItemData();

	void SetItemData(FCountableItemTableData& data);

	virtual UItem* CreateItem() override;
};
