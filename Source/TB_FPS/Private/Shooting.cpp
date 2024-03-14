// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooting.h"

// Sets default values for this component's properties
UShooting::UShooting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UShooting::AttachComponentToCharacter(ACharacter* TargetCharacter)
{
	APlayerController* PlayerController = Cast<APlayerController>(TargetCharacter->GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireIMC, 1);
		}

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UShooting::Fire);
		}
	}
	
}


void UShooting::Fire()
{
	if (ProjectileToSpawn)
	{
		FTransform ProjectileOrigin = this->GetComponentTransform();
		FVector OriginPosition = ProjectileOrigin.GetLocation();
		FRotator OriginRotation = ProjectileOrigin.GetRotation().Rotator();
		FActorSpawnParameters SpawnParamaters;
		SpawnParamaters.Owner = GetOwner();
		SpawnParamaters.Instigator = GetOwner()->GetInstigator();

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileToSpawn, OriginPosition, OriginRotation, SpawnParamaters);
			if (Projectile)
			{
				Projectile->Fire(ProjectileOrigin.GetRotation().GetForwardVector());
			}
		}
		
	}
}

// Called when the game starts
void UShooting::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner()))
	{
		AttachComponentToCharacter(PlayerCharacter);
	}
	
}




