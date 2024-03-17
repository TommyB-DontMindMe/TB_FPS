// Fill out your copyright notice in the Description page of Project Settings.


#include "AirDropEnemy.h"

// Sets default values
AAirDropEnemy::AAirDropEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!Collision)
	{
		Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
		RootComponent = Collision;
		if (!Mesh)
		{
			Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
			Mesh->SetupAttachment(Collision);
		}
	}
}

// Called when the game starts or when spawned
void AAirDropEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirDropEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAirDropEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

