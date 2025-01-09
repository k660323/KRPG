// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include <Define.h>
#include "KRPGAssetManager.generated.h"

class UDataTable;
class UItemData;
struct FStatData;

/**
 * 
 */
UCLASS()
class KRPG_API UKRPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TMap<ECreaturePlayer, TObjectPtr<UDataTable>> PlayerStatTables;

	UPROPERTY()
		TObjectPtr<UDataTable> MonsterStatTable;	

	UPROPERTY()
		TMap<EItemType, TObjectPtr<UDataTable>> ItemTables;
public:
	static UKRPGAssetManager& Get();

public:
	FStatData* GetPlayerStatDataTable(ECreaturePlayer type, int32 level);
	FStatData* GetMonsterStatDataTable(ECreatureMonster type);
	
	UFUNCTION(BlueprintCallable)
	UItemData* GetNewItemData(EItemType type, int32 itemIndex);
protected:
	void InitStatData();
	void InitItemData();
	virtual void StartInitialLoading() override;
};
