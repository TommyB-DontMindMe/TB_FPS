// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "TB_Character.h"
#include "Shooting.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TB_FPS_API UShooting : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShooting();

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "object")
	void AttachComponentToCharacter(ACharacter* TargetCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* FireIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UFUNCTION()
	void Fire();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileToSpawn;
	
};
