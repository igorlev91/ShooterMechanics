// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExhibitionCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UExhibitionMovementComponent;


UENUM(BlueprintType)
enum class EAdvancedStanceMode : uint8
{
	Standing,
	Crouching,
	Prone
};

UCLASS()
class MOVEMENTEXHIBITION_API AExhibitionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExhibitionCharacter(const FObjectInitializer&);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleCrouch();

	virtual void Jump() override;

	virtual void StopJumping() override;

	FORCEINLINE UExhibitionMovementComponent* GetExhibitionMovComponent() { return ExhibitionMovementComponent; };

	FCollisionQueryParams GetIgnoreCollisionParams() const;
	TArray<TObjectPtr<AActor>> GetIgnoredActors();

// Flags
public:
	bool bCustomPressedJump = false;

// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UExhibitionMovementComponent> ExhibitionMovementComponent;


public:

	//~ACharacter interface
	virtual void RecalculateBaseEyeHeight() override;
	virtual bool CanCrouch() const override;
	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;
	virtual void OnRep_IsCrouched() override;
	virtual void OnStartCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust) override;
	//~End of ACharacter interface


#pragma region Prone

	/** Default proned eye height */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float PronedEyeHeight;

	/** Calculates the proned eye height based on movement component settings */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	virtual void RecalculatePronedEyeHeight();

	/** Current active stance mode. */
	UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_StanceMode, Category = "Character")
	EAdvancedStanceMode StanceMode;

	/** Returns the current active stance mode. */
	UFUNCTION(BlueprintPure, Category = "Character")
	FORCEINLINE EAdvancedStanceMode GetStanceMode() const { return StanceMode; };

	/**
	 * Request the character to change the walkig mode.
	 * The request is processed on the next update of the CharacterMovementComponent.
	 */
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetStanceMode(const EAdvancedStanceMode NewStanceMode);

	/**
	 * True if the current stance mode can be changed in the next update.
	 */
	virtual bool CanSetStanceMode() const;

	/** Handle change stance mode replicated from server */
	UFUNCTION()
	virtual void OnRep_StanceMode();

	/**
	 * Called when Character changes the stance mode. Called on non-owned Characters through StanceMode replication.
	 * @param	HalfHeightAdjust		difference between default collision half-height, and actual proned capsule half-height.
	 * @param	ScaledHalfHeightAdjust	difference after component scale is taken in to account.
	 * @param	StanceMode				new stance mode.
	 */
	virtual void OnStanceModeChanged(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust, const EAdvancedStanceMode NewStanceMode);

	/**
	 * Event when Character changes the stance mode.
	 * @param	HalfHeightAdjust		difference between default collision half-height, and actual proned capsule half-height.
	 * @param	ScaledHalfHeightAdjust	difference after component scale is taken in to account.
	 * @param	StanceMode				new stance mode.
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStanceModeChanged", ScriptName = "OnStanceModeChanged"))
	void K2_OnStanceModeChanged(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust, const EAdvancedStanceMode NewStanceMode);

#pragma endregion Prone
};
