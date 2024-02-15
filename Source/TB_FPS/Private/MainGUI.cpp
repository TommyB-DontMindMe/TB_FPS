// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGUI.h"

void UMainGUI::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
	
}
