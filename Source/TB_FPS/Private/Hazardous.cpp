// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazardous.h"

// Sets default values for this component's properties
UHazardous::UHazardous()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHazardous::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorHit.AddDynamic(this, &UHazardous::OnActorHit);
}

void UHazardous::OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UHealth* TargetHealth = OtherActor->GetComponentByClass<UHealth>();
	OnDamage.BindUObject<UHealth>(TargetHealth, &UHealth::TakeDamage);
	if (OnDamage.IsBound())
	{
		OnDamage.Execute(DamageRating);
	}
}


// Called every frame
void UHazardous::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



