// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExhibitionCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MOVEMENTEXHIBITION_API AExhibitionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExhibitionCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleCrouch();

// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;
};
