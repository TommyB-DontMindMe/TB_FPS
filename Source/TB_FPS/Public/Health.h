// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "HealthBar.h"
#include "TimerManager.h"
#include "Engine/TimerHandle.h"
#include "Health.generated.h"


DECLARE_DELEGATE_OneParam(FDamageDelegate, float)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TB_FPS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthValue = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float GraceDuration = 3;
	bool IsGraceState = false;
	FTimerHandle GraceTimer;

	void GraceComplete();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UHealthBar* PlayerUIElement = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = "Health")
	void TakeDamage(float HealthDelta);
	UFUNCTION(Category = "Health")
	void Die();

	void SetUIElement(UHealthBar* NewUIElement);
};
