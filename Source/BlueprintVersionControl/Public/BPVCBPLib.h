// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "BPVCBPLib.generated.h"
/**
 * 
 */
UCLASS()
class BLUEPRINTVERSIONCONTROL_API UBPVCBPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static void IterateBlueprints();

	UFUNCTION(BlueprintCallable)
	static UBlueprint* LoadAndCastBlueprint(FString AssetPath);

	UFUNCTION(BlueprintCallable)
	static void IterateNodesInBlueprints(UBlueprint* Blueprint);
	
	UFUNCTION(BlueprintCallable)
	static void SaveAllBlueprints();
};
