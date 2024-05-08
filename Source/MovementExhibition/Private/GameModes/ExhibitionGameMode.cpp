// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ExhibitionGameMode.h"

#include "Characters/BaseCharacter.h"
#include "Controllers/ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AExhibitionGameMode::BeginPlay()
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

void AExhibitionGameMode::OnCharacterTakeDamage(AController* ControllerDamaged, AController* ControllerCauser)
{
	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterHitSomeone();
	}
}

void AExhibitionGameMode::OnCharacterDeath(ACharacter* Character, AController* ControllerCauser)
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

void AExhibitionGameMode::OnCharacterBrokenShield(ACharacter* Character, AController* ControllerCauser)
{
	if (AShooterPlayerController* ShooterController = Cast<AShooterPlayerController>(ControllerCauser))
	{
		ShooterController->OnCharacterBrokeShield();
	}
}

void AExhibitionGameMode::RegisterController(AController* NewController)
{
	if (KillCounterMapping.Contains(NewController))
	{
		return;
	}

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(NewController->GetCharacter()))
	{ 
		if (!Character->OnTakeDamage().IsAlreadyBound(this, &AExhibitionGameMode::OnCharacterTakeDamage))
		{
			Character->OnTakeDamage().AddDynamic(this, &AExhibitionGameMode::OnCharacterTakeDamage);
		}
		if (!Character->OnCharacterDeath().IsAlreadyBound(this, &AExhibitionGameMode::OnCharacterDeath))
		{
			Character->OnCharacterDeath().AddDynamic(this, &AExhibitionGameMode::OnCharacterDeath);
		}
		if (!Character->OnCharacterShieldBroken().IsAlreadyBound(this, &AExhibitionGameMode::OnCharacterBrokenShield))
		{
			Character->OnCharacterShieldBroken().AddDynamic(this, &AExhibitionGameMode::OnCharacterBrokenShield);
		}

		KillCounterMapping.Add(NewController, 0);
	}
}


void AExhibitionGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	RegisterController(NewPlayer);
}