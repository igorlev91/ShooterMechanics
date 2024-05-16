// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerUtils.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTEXHIBITION_API UPlayerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool ComputeScreenCenterAndDirection(const APlayerController* Player, FVector& CenterLocation, FVector& CenterDirection);
};