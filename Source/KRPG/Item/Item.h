// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UItemData;
/**
 * 
 */
UCLASS(config = Game, BlueprintType, meta = (ShortTooltip = "Item"))
class KRPG_API UItem : public UObject
{
	GENERATED_BODY()
	
protected:
		UItemData* ItemData;

public:
	UItem();
 
	UFUNCTION(BlueprintCallable)
		UItemData* GetItemData();

	void SetItemData(UItemData& data);
};
