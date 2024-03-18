// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyList.Num() < SpawnAmount)
	{
		AActor* SpawnedEnemy = nullptr;
		UWorld* World = GetWorld();
		if (World && EnemyType)
		{
			FVector SpawnAt = GetActorLocation();
			SpawnAt.X = SpawnAt.X + FMath::RandRange(-SpawnRange, SpawnRange);
			SpawnAt.Y = SpawnAt.Y + FMath::RandRange(-SpawnRange, SpawnRange);
			SpawnedEnemy = World->SpawnActor<AActor>(EnemyType, SpawnAt, FRotator::ZeroRotator);
			EnemyList.Add(SpawnedEnemy);
		}
	}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerDelegate, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true, 5);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

