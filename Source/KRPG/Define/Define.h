// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.generated.h"
/**
 * 
 */

 // 삭제하면 구멍날수 있음 그럴경우 파일 열어서 수정
//#define ECC_Attack ECollisionChannel::ECC_Game

#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Item ECollisionChannel::ECC_GameTraceChannel2

class KRPG_API Define
{
public:
	Define();
	~Define();
};


UENUM(BlueprintType)
enum class EFStat : uint8
{
	STR,
	INT,
	DEX,
	LUK
};

UENUM(BlueprintType)
enum class ECreaturePlayer : uint8
{
	None,
	Countness
};

UENUM(BlueprintType)
enum class ECreatureMonster : uint8
{
	None,
	Goblin,
	IceGoblin,
	WizardGoblin
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None,
	Physical,
	Magic
};

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None		UMETA(DisplayName = "None"),
	Idle		UMETA(DisplayName = "Idle"),
	Move		UMETA(DisplayName = "Move"),
	Dodge		UMETA(DisplayName = "Dodge"),
	Roll		UMETA(DisplayName = "Roll"),
	Run			UMETA(DisplayName = "Run"),
	Jump		UMETA(DisplayName = "Jump"),
	Patrol		UMETA(DisplayName = "Patrol"),
	CrouchDown	UMETA(DisplayName = "CrouchDown"),
	Attack		UMETA(DisplayName = "Attack"),
	Skill		UMETA(DisplayName = "Skill"),
	Hit			UMETA(DisplayName = "Hit"),
	CC			UMETA(DisplayName = "CC"),
	Chase		UMETA(DisplayName = "Chase"),
	Return		UMETA(DisplayName = "Return"),
	Die			UMETA(DisplayName = "Die")
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	None,
	Common,
	UnCommon,
	Rare,
	Unique,
	Legendary,
	Epic
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Weapon,
	Armor,
	Countable,
	Portion,
	Etc
};


UENUM(BlueprintType)
enum class EEquipType : uint8
{
	None,
	Weapon,
	Shoulder,
	Top,
	Belt,
	Bottom,
	Shoes,
	Ring,
	Rracelet,
	Necklace,
	AuxiliaryEquipment,
	MagicStone,
	Earring
};