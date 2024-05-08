// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Gameplay/Items/AmmoItem.h"
#include "ShooterPlayerController.generated.h"

class ABaseCharacter;
class UInputAction;
class UPlayerHud;

/**
 * 
 */
UCLASS()
class MOVEMENTEXHIBITION_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// This is used by PlayerHUD
	UFUNCTION(BlueprintPure)
	bool HasAmmoInventory() const;

	// This is used by PlayerHUD
	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeaponAmmo() const;

	// This is used by PlayerHUD
	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeaponMaxAmmo() const;

	// This is used by PlayerHUD
	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeaponAmmoStorage() const;

	// This is used by PlayerHUD
	UFUNCTION(BlueprintPure)
	EAmmoType GetCurrentWeaponAmmoType() const;

// Callbacks
protected:
	UFUNCTION()
	void OnCharacterReady(ACharacter* InstigatorCharacter);
	
	UFUNCTION()
	void OnCharacterAbsorbShieldDamage(ACharacter* InstigatorCharacter, const float AbsorbedDamage, const float NewShieldValue);

	UFUNCTION()
	void OnCharacterTakeHealthDamage(ACharacter* InstigatorCharacter, const float TakenDamage, const float NewHealthValue);

	UFUNCTION()
	void OnCharacterRegenShield(ACharacter* InstigatorCharacter, const float RegenAmount, const float NewShieldValue);

	UFUNCTION()
	void OnCharacterRegenHealth(ACharacter* InstigatorCharacter, const float RegenAmount, const float NewHealthValue);

protected:
	void InitializeHud();
	void InitializeHudDelegates();
	
// Action functions
protected:
	void RequestJumpAction();
	void RequestStopJumpAction();
	void RequestMoveAction(const FInputActionValue&);
	void RequestLookAction(const FInputActionValue&);
	void RequestSprintAction();
	void RequestWeaponPullTriggerAction();
	void RequestWeaponReleaseTriggerAction();
	void RequestReloadWeapon();
	

// Properties
protected:
	UPROPERTY(Transient)
	TObjectPtr<ABaseCharacter> BaseCharacterRef;

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UPlayerHud> PlayerHudClass;

	UPROPERTY(Transient)
	TObjectPtr<UPlayerHud> PlayerHudRef;
	
// Bindings
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> StopJumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UInputAction> PullTriggerAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ReleaseTriggerAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;

};