// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovementExhibitionGameModeBase.h"

#include "Characters/BaseCharacter.h"
#include "Controllers/ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMovementExhibitionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Characters; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Characters);

	for (AActor* Actor : Characters)
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(Actor))
		{
			Character->OnTakeDamage().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterTakeDamage);
			Character->OnCharacterDeath().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterDeath);
		}
	}
}

void AMovementExhibitionGameModeBase::OnCharacterTakeDamage(AController* ControllerDamaged, AController* ControllerCauser)
{
	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterHitSomeone();
	}
}

void AMovementExhibitionGameModeBase::OnCharacterDeath(ACharacter* Character, AController* ControllerCauser)
{
	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterKillSomeone();
	}
}
