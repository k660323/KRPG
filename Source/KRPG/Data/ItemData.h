// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemDataTable.h"
#include "ItemData.generated.h"

class UItem;
/**
 * 
 */
UCLASS(config = Game, BlueprintType, meta = (ShortTooltip = "ItemData"))
class KRPG_API UItemData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		EItemGrade ItemGrade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UStaticMesh* WorldItemMesh;
public:
	UItemData();

	void SetItemData(FItemTableData& data);
	
	virtual UItem* CreateItem();
};
