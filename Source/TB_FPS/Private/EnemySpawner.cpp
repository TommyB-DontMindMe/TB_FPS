// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!SpawnArea)
	{
		SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyList.Num() < SpawnAmount)
	{
		AActor* SpawnedEnemy = nullptr;
		UWorld* World = GetWorld();
		if (World && EnemyType)
		{
			SpawnedEnemy = World->SpawnActor<AActor>(EnemyType, GetActorLocation(), FRotator::ZeroRotator);
			EnemyList.Add(SpawnedEnemy);
		}
	}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerDelegate, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true, 10);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

