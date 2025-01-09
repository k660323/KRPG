// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CountableItemData.h"
#include "PortionItemData.generated.h"

class UPortionItem;
/**
 * 
 */
UCLASS()
class KRPG_API UPortionItemData : public UCountableItemData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortionItem")
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortionItem")
		TSubclassOf<UPortionItem> PortionSubClass;
public:
	UPortionItemData();

	void SetItemData(FPortionItemTableData& data);

	virtual UItem* CreateItem() override;
};
