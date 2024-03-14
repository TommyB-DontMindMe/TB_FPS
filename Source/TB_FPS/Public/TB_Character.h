// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "MainGUI.h"
#include "Health.h"
#include "Math/Rotator.h"
#include "TB_Character.generated.h"

UCLASS()
class TB_FPS_API ATB_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATB_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variables for Internal use
	float CameraArmPitch = -30.f;
	UUserWidget* UIInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
	class USkeletalMeshComponent* Playermesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USceneComponent* ThirdPersonFocus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArm { nullptr };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* ThirdPersonCamera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* FirstPersonCamera = nullptr;

	// UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GUI")
	TSubclassOf<UMainGUI> WidgetComponent;
	UFUNCTION()
	UUserWidget* GetUI();
	void SetUI(UUserWidget* NewUI);




	// Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputMappingContext* IMC_GenericInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	float Speed = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Zoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Jump;



	void MoveAction(const FInputActionValue&);
	void RotateCamera(const FInputActionValue&);
	void ZoomUnzoom(const FInputActionValue&);
	void JumpStarted();
	void JumpEnded();
};
