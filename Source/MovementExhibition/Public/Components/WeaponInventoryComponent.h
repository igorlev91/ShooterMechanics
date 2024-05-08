// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInventoryComponent.generated.h"

class ABaseCharacter;
class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTEXHIBITION_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool EquipDefaultWeapon();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Weapon Inventory Interface
public:
	UFUNCTION(BlueprintCallable)
	bool EquipWeapon(ABaseWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	UFUNCTION(BlueprintCallable)
	void ReleaseTrigger();

	FORCEINLINE ABaseWeapon* GetCurrentWeapon() { return CurrentWeaponRef; };
	
// Properties
protected:
	UPROPERTY(Transient)
	TObjectPtr<ABaseCharacter> BaseCharacterRef;

	UPROPERTY(Transient)
	TObjectPtr<ABaseWeapon> CurrentWeaponRef;

	UPROPERTY(EditAnywhere, Category="Weapon")
	FName ShooterSocketAttachName = NAME_None;
	
	UPROPERTY(EditAnywhere, Category="Weapon")
	bool bEquipDefaultWeaponOnBegin = true;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	TArray<TObjectPtr<ABaseWeapon>> WeaponInventory;
};