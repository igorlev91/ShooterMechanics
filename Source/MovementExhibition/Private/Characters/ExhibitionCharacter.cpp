// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ExhibitionCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ExhibitionMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AExhibitionCharacter::AExhibitionCharacter(const FObjectInitializer& Initializer) :
	Super(Initializer.SetDefaultSubobjectClass<UExhibitionMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	ExhibitionMovementComponent = Cast<UExhibitionMovementComponent>(GetCharacterMovement());
	ExhibitionMovementComponent->SetIsReplicated(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraBoom);
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	JumpMaxHoldTime = 0.15f;
	GetCharacterMovement()->AirControl = 0.5f;

	// Data members
	StanceMode = EAdvancedStanceMode::Standing;
}

// Called when the game starts or when spawned
void AExhibitionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExhibitionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExhibitionCharacter::ToggleCrouch()
{
	ensure(ExhibitionMovementComponent);

	ExhibitionMovementComponent->ToggleCrouch();
}

void AExhibitionCharacter::Jump()
{
	if (ExhibitionMovementComponent->IsCrouching())
	{
		ExhibitionMovementComponent->ToggleCrouch();
	}
	else
	{
		bCustomPressedJump = true;
		Super::Jump();
		bPressedJump = false;
	}
}

void AExhibitionCharacter::StopJumping()
{
	bCustomPressedJump = false;
	Super::StopJumping();
}

FCollisionQueryParams AExhibitionCharacter::GetIgnoreCollisionParams() const
{
	TArray<AActor*> ChildActors;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetAllChildActors(ChildActors);
	Params.AddIgnoredActors(Children);
	
	return Params;
}

TArray<TObjectPtr<AActor>> AExhibitionCharacter::GetIgnoredActors()
{
	TArray<TObjectPtr<AActor>> IgnoredActors;
	GetAllChildActors(IgnoredActors);
	IgnoredActors.Add(this);
	
	return IgnoredActors;
}


void AExhibitionCharacter::RecalculateBaseEyeHeight()
{
	switch (StanceMode)
	{
	case EAdvancedStanceMode::Crouching:
		BaseEyeHeight = CrouchedEyeHeight;
		break;
	case EAdvancedStanceMode::Prone:
		BaseEyeHeight = PronedEyeHeight;
		break;
	default:	// Standing
		BaseEyeHeight = GetDefault<APawn>(GetClass())->BaseEyeHeight;
		break;
	}
}

bool AExhibitionCharacter::CanCrouch() const
{
	// DO NOTHING
	return false;
}

void AExhibitionCharacter::Crouch(bool bClientSimulation)
{
	// DO NOTHING
}

void AExhibitionCharacter::UnCrouch(bool bClientSimulation)
{
	// DO NOTHING
}

void AExhibitionCharacter::OnRep_IsCrouched()
{
	// DO NOTHING
}

void AExhibitionCharacter::OnStartCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust)
{
	// DO NOTHING
}

void AExhibitionCharacter::OnEndCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust)
{
	// DO NOTHING
}

void AExhibitionCharacter::RecalculatePronedEyeHeight()
{
	//TODO
}

void AExhibitionCharacter::SetStanceMode(const EAdvancedStanceMode NewStanceMode)
{
	check(ExhibitionMovementComponent);

	if (ExhibitionMovementComponent && CanSetStanceMode())
	{
		switch (NewStanceMode)
		{
		case EAdvancedStanceMode::Crouching:
			//ExhibitionMovementComponent->Safe_bWantsToCrouch = true;
			break;
		case EAdvancedStanceMode::Prone:
			ExhibitionMovementComponent->Safe_bWantsToProne = true;
			break;
		default: // standing
			ExhibitionMovementComponent->Safe_bWantsToStand = true;
			break;
		}
	}
}

bool AExhibitionCharacter::CanSetStanceMode() const
{
	return ExhibitionMovementComponent && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void AExhibitionCharacter::OnRep_StanceMode()
{
	check(ExhibitionMovementComponent);

	if (ExhibitionMovementComponent)
	{
		if (StanceMode == EAdvancedStanceMode::Standing)
		{
			ExhibitionMovementComponent->Stand(true);
		}
		else if (StanceMode == EAdvancedStanceMode::Crouching)
		{
			ExhibitionMovementComponent->Crouch(true);
		}
		else if (StanceMode == EAdvancedStanceMode::Prone)
		{
			ExhibitionMovementComponent->Prone(true);
		}

		ExhibitionMovementComponent->bNetworkUpdateReceived = true;
	}
}

void AExhibitionCharacter::OnStanceModeChanged(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust, const EAdvancedStanceMode NewStanceMode)
{
	RecalculateBaseEyeHeight();

	const ACharacter* DefaultChar = GetDefault<ACharacter>(GetClass());
	USkeletalMeshComponent* DefaultSKMesh = DefaultChar->GetMesh();
	USkeletalMeshComponent* SKMesh = GetMesh();
	if (SKMesh && DefaultSKMesh)
	{
		FVector& MeshRelativeLocation = SKMesh->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultSKMesh->GetRelativeLocation().Z + HalfHeightAdjust;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z + HalfHeightAdjust;
	}

	K2_OnStanceModeChanged(HalfHeightAdjust, ScaledHalfHeightAdjust, NewStanceMode);
}