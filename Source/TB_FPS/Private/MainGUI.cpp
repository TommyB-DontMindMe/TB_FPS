// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGUI.h"


bool UMainGUI::ConfigureHealthBar()
{
	UHealth* PlayerHealthComponent = GetOwningPlayerPawn()->GetComponentByClass<UHealth>();
	
	if (PlayerHealthComponent)
	{
		PlayerHealthComponent->SetUIElement(HealthBar);
		return true;
	}
	return false;
}
