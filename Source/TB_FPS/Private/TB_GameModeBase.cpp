// Fill out your copyright notice in the Description page of Project Settings.


#include "TB_GameModeBase.h"

void ATB_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ATB_Character* PlayerCharacter = Cast<ATB_Character>(GetWorld()->GetFirstPlayerController());
	//PlayerCharacter->OnDestroyed.AddDynamic(this, &ATB_GameModeBase::Respawn);
}

void ATB_GameModeBase::Respawn(AActor* DeadActor)
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();

	RestartPlayerAtPlayerStart(Player, RespawnPoint);
}
