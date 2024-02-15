// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

}



// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::TakeDamage(float HealthDelta)
{
	
	if (!IsGraceState || HealthDelta > 0)
	{
		float RemainingHealth = HealthValue + HealthDelta;
	HealthValue = RemainingHealth < 0 ? 0 : RemainingHealth > MaxHealth? MaxHealth : RemainingHealth;
		if (HealthValue == 0)
		{
			UHealth::Die();
		}

		if (PlayerUI)
		{
			PlayerUI->UpdateHealthBar(HealthValue, MaxHealth);
		}

		IsGraceState = true;
		GetOwner()->GetWorldTimerManager().SetTimer(GraceTimer, this, &UHealth::GraceComplete, GraceDuration);
	}
}

void UHealth::GraceComplete()
{
	IsGraceState = false;
	GetOwner()->GetWorldTimerManager().ClearTimer(GraceTimer);
}

void UHealth::Die()
{
	GetOwner()->Destroy();
}

void UHealth::SetUI(UMainGUI* NewUI)
{
	PlayerUI = NewUI;
}

