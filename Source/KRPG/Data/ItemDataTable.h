// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <Define.h>
#include "ItemDataTable.generated.h"

class UItem;
class UPortionItem;

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
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
	FItemTableData();
};

USTRUCT(BlueprintType)
struct FCountableItemTableData : public FItemTableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountableItem")
		int32 MaxAmount;

public:
	FCountableItemTableData();
};

USTRUCT(BlueprintType)
struct FPortionItemTableData : public FCountableItemTableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortionItem")
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortionClass")
		TSubclassOf<UPortionItem> PortionSubClass;

public:
	FPortionItemTableData();
};

USTRUCT(BlueprintType)
struct FEquipmentItemTableData : public FItemTableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		EEquipType EquipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 RequireLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		bool InfinityDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentItem")
		int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 LUK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AtkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Critical;
public:
	FEquipmentItemTableData();
};

USTRUCT(BlueprintType)
struct FWeaponTableItemData : public FEquipmentItemTableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int32 PhysicalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int32 MagicDamage;
public:
	FWeaponTableItemData();
};

USTRUCT(BlueprintType)
struct FArmorTableItemData : public FEquipmentItemTableData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 PhysicalDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MagicDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float HpRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MpRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float JumpZVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float AirControl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MaxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		float MinAnalogWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int32 MaxMp;
public:
	FArmorTableItemData();
};

/**
 * 
 */
UCLASS()
class KRPG_API UItemDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
