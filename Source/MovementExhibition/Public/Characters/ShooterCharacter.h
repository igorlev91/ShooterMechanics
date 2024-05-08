// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "ShooterCharacter.generated.h"

class UShieldComponent;
class UPlayerHud;

/**
 * 
 */
UCLASS()
class MOVEMENTEXHIBITION_API AShooterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	
public:
	AShooterCharacter();

	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	float GetMaxShield() const;

	float GetCurrentShield() const;

	bool AddHealthRegen(const float& HealthAmount);
	bool AddShieldRegen(const float& ShieldAmount);

protected:
	void OnShieldBroken();

// Components
protected:
	//UPROPERTY(VisibleAnywhere, NoClear)
	//TObjectPtr<UShieldComponent> ShieldComponent;

protected:
	UPROPERTY(Transient)
	TObjectPtr<APlayerController> PCBase;
	
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UPlayerHud> PlayerHudClass;

	UPROPERTY(Transient)
	TObjectPtr<UPlayerHud> PlayerHudRef;
};
