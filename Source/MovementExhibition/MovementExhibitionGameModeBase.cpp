// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovementExhibitionGameModeBase.h"

#include "Characters/BaseCharacter.h"
#include "Controllers/ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMovementExhibitionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	KillCounterMapping.Empty();

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Characters);

	for (AActor* Actor : Characters)
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(Actor))
		{
			Character->OnTakeDamage().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterTakeDamage);
			Character->OnCharacterDeath().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterDeath);
			Character->OnCharacterShieldBroken().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterBrokenShield);
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
	if (!KillCounterMapping.Contains(ControllerCauser))
	{
		KillCounterMapping.Add(ControllerCauser, 1);
	}
	else
	{
		KillCounterMapping[ControllerCauser] += 1;
	}

	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterKillSomeone(KillCounterMapping[ControllerCauser]);
	}
}


void AMovementExhibitionGameModeBase::OnCharacterBrokenShield(ACharacter* Character, AController* ControllerCauser)
{
	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterBrokeShield();
	}
}
