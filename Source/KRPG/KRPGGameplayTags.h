// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FKRPGGameplayTags
{
public:
	static const FKRPGGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

public:
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;
	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_R;
	FGameplayTag InputTag_T;
	FGameplayTag InputTag_I;
	FGameplayTag InputTag_O;
	FGameplayTag InputTag_F;
	FGameplayTag InputTag_G;
	FGameplayTag InputTag_L;
	FGameplayTag InputTag_LShift;
	FGameplayTag InputTag_Z;
	FGameplayTag InputTag_X;
	FGameplayTag InputTag_C;
	FGameplayTag InputTag_V;
	FGameplayTag InputTag_B;
	FGameplayTag InputTag_LCtrl;
	FGameplayTag InputTag_LALT;
	FGameplayTag InputTag_SpaceBar;
private:
	static FKRPGGameplayTags GameplayTags;

};