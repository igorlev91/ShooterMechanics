// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExhibitionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTEXHIBITION_API AExhibitionGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Delegates
protected:
	UFUNCTION()
	void OnCharacterTakeDamage(AController* ControllerDamaged, AController* ControllerCauser);

	UFUNCTION()
	void OnCharacterDeath(ACharacter* Character, AController* ControllerCauser);

	UFUNCTION()
	void OnCharacterBrokenShield(ACharacter* Character, AController* ControllerCauser);
public:
	void RegisterController(AController* NewController);

	// Properties
protected:
	UPROPERTY(Transient)
	TMap<AController*, int32> KillCounterMapping;
};
