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

	if (!ThirdPersonFocus)
	{
		ThirdPersonFocus = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdPersonFocus"));
		ThirdPersonFocus->SetupAttachment(GetRootComponent());

		if (!SpringArm)
		{
			SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
			SpringArm->bDoCollisionTest = false;
			SpringArm->SetUsingAbsoluteRotation(true);

			SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
			SpringArm->TargetArmLength = 50.f;
			SpringArm->bEnableCameraLag = false;
			SpringArm->CameraLagSpeed = 5.f;
			SpringArm->SetupAttachment(ThirdPersonFocus);

			if (!ThirdPersonCamera)
			{
				ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
				ThirdPersonCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
			}
		}
	}
	if (!FirstPersonCamera)
	{
		FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FirstPersonCamera->SetupAttachment(GetRootComponent());

		FirstPersonCamera->bUsePawnControlRotation = true;
	}
	

}

// Called when the game starts or when spawned
void ATB_Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(IMC_GenericInputContext, 0);
		}
		PlayerController->SetViewTarget(this);
		if (WidgetComponent)
		{
			UIInstance = CreateWidget<UUserWidget>(PlayerController, WidgetComponent);
			UIInstance->AddToViewport();
			Cast<UMainGUI>(UIInstance)->ConfigureHealthBar();
		}
	}
	ThirdPersonCamera->SetActive(false);
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



UUserWidget* ATB_Character::GetUI()
{
	return UIInstance;
}

void ATB_Character::SetUI(UUserWidget* NewUI)
{
	UIInstance = NewUI;
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
	if (FirstPersonCamera->IsActive())
	{
		AddControllerYawInput(GetValue.X);
		AddControllerPitchInput(-GetValue.Y);
	}
	else
	{
		AddControllerYawInput(GetValue.X);
		AddControllerPitchInput(GetValue.Y);
		CameraArmPitch = FMath::Clamp(CameraArmPitch + GetValue.Y / 5, -90.f, 0);
		SpringArm->SetRelativeRotation(FRotator(CameraArmPitch, GetControlRotation().Yaw, 0.f));
	}
	
	
}

void ATB_Character::ZoomUnzoom(const FInputActionValue& Value)
{
	const float GetValue = Value.Get<float>();
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + GetValue * 50, 50, 1000);
	// Switch between First person and Third person camera
	if (SpringArm->TargetArmLength > 50)
	{
		// Switch to third person Camera
		ThirdPersonCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
	}
	else
	{
		// Switch to first person Camera
		FirstPersonCamera->SetActive(true);
		ThirdPersonCamera->SetActive(false);
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
