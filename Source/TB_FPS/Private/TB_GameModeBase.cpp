// Fill out your copyright notice in the Description page of Project Settings.


#include "TB_GameModeBase.h"

void ATB_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ATB_Character* PlayerCharacter = Cast<ATB_Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnDestroyed.AddDynamic(this, &ATB_GameModeBase::Respawn);
	}
}



void ATB_GameModeBase::Respawn(AActor* DeadActor)
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	UUserWidget* InheritedUI = Cast<ATB_Character>(DeadActor)->GetUI();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = TEXT("PlayerReborn");
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ATB_Character* PlayerActor = GetWorld()->SpawnActor<ATB_Character>(DefaultPawnClass, RespawnPoint, FRotator().ZeroRotator, SpawnParams);
	PlayerActor->SetUI(InheritedUI);
	Player->Possess(PlayerActor);
}
