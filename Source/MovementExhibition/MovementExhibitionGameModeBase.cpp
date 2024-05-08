// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovementExhibitionGameModeBase.h"

#include "Characters/BaseCharacter.h"
#include "Controllers/ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMovementExhibitionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	KillCounterMapping.Empty();

	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), Controllers);

	for (AActor* ControllerActor : Controllers)
	{
		if (AController* Controller = Cast<AController>(ControllerActor))
		{
			RegisterController(Controller);
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

void AMovementExhibitionGameModeBase::RegisterController(AController* NewController)
{
	if (KillCounterMapping.Contains(NewController))
	{
		return;
	}

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(NewController->GetCharacter()))
	{
		if (!Character->OnTakeDamage().IsAlreadyBound(this, &AMovementExhibitionGameModeBase::OnCharacterTakeDamage))
		{
			Character->OnTakeDamage().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterTakeDamage);
		}
		if (!Character->OnCharacterDeath().IsAlreadyBound(this, &AMovementExhibitionGameModeBase::OnCharacterDeath))
		{
			Character->OnCharacterDeath().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterDeath);
		}
		if (!Character->OnCharacterShieldBroken().IsAlreadyBound(this, &AMovementExhibitionGameModeBase::OnCharacterBrokenShield))
		{
			Character->OnCharacterShieldBroken().AddDynamic(this, &AMovementExhibitionGameModeBase::OnCharacterBrokenShield);
		}

		KillCounterMapping.Add(NewController, 0);
	}
}