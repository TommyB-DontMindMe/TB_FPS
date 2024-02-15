// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TB_Character.h"
#include "TB_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TB_FPS_API ATB_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector RespawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	float RespawnDelay;
	
	UFUNCTION()
	void Respawn(AActor* DeadActor);
	FActorDestroyedSignature DestroyDelegate;
};
