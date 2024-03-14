// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TB_FPS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Enemy Class
	TSubclassOf<AActor> EnemyType;
	// Spawn Rate
	float SpawnRate = 15;

	bool HaltSpawn;

	UFUNCTION()
	AActor* SpawnEnemy()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawned Enemies
	TArray<AActor> EnemyList;

};
