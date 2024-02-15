// Fill out your copyright notice in the Description page of Project Settings.


#include "TB_Character.h"


// Sets default values
ATB_Character::ATB_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMC_GenericInputContext, 0);
		}
	}


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 50.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ATB_Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem) {
			subsystem->AddMappingContext(IMC_GenericInputContext, 0);
		}
		PlayerController->SetViewTarget(this);
		if (WidgetComponent)
		{
			UUserWidget* NewGUI = CreateWidget<UUserWidget>(PlayerController, WidgetComponent);
			NewGUI->AddToViewport();
			GetComponentByClass<UHealth>()->SetUI(CastChecked<UMainGUI>(NewGUI));
		}
	}
	Camera->SetActive(false);
}




// Called every frame
void ATB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputCom->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATB_Character::MoveAction);
		EnhancedInputCom->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &ATB_Character::RotateCamera);
		EnhancedInputCom->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ATB_Character::ZoomUnzoom);
		EnhancedInputCom->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ATB_Character::JumpStarted);
		EnhancedInputCom->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ATB_Character::JumpEnded);
	}
}

void ATB_Character::MoveAction(const FInputActionValue& Value)
{
	const FVector2D GetValue = Value.Get<FVector2D>();
	FVector Direction = this->GetActorForwardVector() * GetValue.Y + this->GetActorRightVector() * GetValue.X;
	this->AddMovementInput(Direction, Speed);
}

void ATB_Character::RotateCamera(const FInputActionValue& Value)
{
	const FVector2D GetValue = Value.Get<FVector2D>();
	AddControllerYawInput(GetValue.X);
	AddControllerPitchInput(-GetValue.Y);
	CameraArmPitch = FMath::Clamp(CameraArmPitch + GetValue.Y / 5,-90.f,0);
	SpringArm->SetRelativeRotation(FRotator(CameraArmPitch, GetControlRotation().Yaw, 0.f));
	
}

void ATB_Character::ZoomUnzoom(const FInputActionValue& Value)
{
	const float GetValue = Value.Get<float>();
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + GetValue * 50, 50, 1000);
	// Switch between First person and Third person camera
	if (SpringArm->TargetArmLength > 50)
	{
		// Switch to Camera
		Camera->SetActive(true);
	}
	else
	{
		// Switch to default Camera
		Camera->SetActive(false);
	}
}

void ATB_Character::JumpStarted()
{
	bPressedJump = true;
}
void ATB_Character::JumpEnded()
{
	bPressedJump = false;
}
