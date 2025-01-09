// Fill out your copyright notice in the Description page of Project Settings.


#include "KRPGGameplayTags.h"
#include "GameplayTagsManager.h"


FKRPGGameplayTags FKRPGGameplayTags::GameplayTags;

void FKRPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
	);

	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.5"),
		FString("Input Tag for 5 key")
	);

	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Q"),
		FString("Input Tag for Q key")
	);

	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.E"),
		FString("Input Tag for E key")
	);

	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.R"),
		FString("Input Tag for R key")
	);

	GameplayTags.InputTag_T = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.T"),
		FString("Input Tag for T key")
	);

	GameplayTags.InputTag_I = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.I"),
		FString("Input Tag for I key")
	);

	GameplayTags.InputTag_O = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.O"),
		FString("Input Tag for O key")
	);

	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.F"),
		FString("Input Tag for F key")
	);

	GameplayTags.InputTag_G = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.G"),
		FString("Input Tag for G key")
	);

	GameplayTags.InputTag_L = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.L"),
		FString("Input Tag for L key")
	);

	GameplayTags.InputTag_LShift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LShift"),
		FString("Input Tag for LShift key")
	);

	GameplayTags.InputTag_Z = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Z"),
		FString("Input Tag for Z key")
	);

	GameplayTags.InputTag_X = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.X"),
		FString("Input Tag for X key")
	);

	GameplayTags.InputTag_C = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.C"),
		FString("Input Tag for C key")
	);

	GameplayTags.InputTag_V = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.V"),
		FString("Input Tag for V key")
	);

	GameplayTags.InputTag_B = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.B"),
		FString("Input Tag for B key")
	);

	GameplayTags.InputTag_LCtrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LCtrl"),
		FString("Input Tag for LCtrl key")
	);

	GameplayTags.InputTag_LALT = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LALT"),
		FString("Input Tag for LALT key")
	);

	GameplayTags.InputTag_SpaceBar = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.SpaceBar"),
		FString("Input Tag for SpaceBar key")
	);
}
