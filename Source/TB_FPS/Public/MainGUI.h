// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/ProgressBar.h"
#include "Health.h"
#include "MainGUI.generated.h"

/**
 * 
 */
UCLASS()
class TB_FPS_API UMainGUI : public UUserWidget
{
	GENERATED_BODY()

public:
	bool ConfigureHealthBar();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	class UHealthBar* HealthBar;

};
