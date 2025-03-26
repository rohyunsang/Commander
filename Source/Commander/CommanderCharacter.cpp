// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommanderCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACommanderCharacter

ACommanderCharacter::ACommanderCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	
}

void ACommanderCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipWeaponToHand();
}

void ACommanderCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ACommanderCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACommanderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACommanderCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACommanderCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACommanderCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACommanderCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACommanderCharacter::EquipWeaponToHand()
{
	// 1. WeaponMeshReference와 GetMesh() 확인
	if (!WeaponMeshReference)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponMeshReference is null. Make sure the mesh is properly loaded."));
		return;
	}

	if (!GetMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("GetMesh() returned null. Make sure the character mesh is set up properly."));
		return;
	}

	// 2. 스켈레톤 메시 컴포넌트 가져오기
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get SkeletalMeshComponent."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("MeshComponent found: %s"), *MeshComponent->GetName());

	// 3. 무기 메시를 별도의 컴포넌트로 추가 (SetSkeletalMesh 대신)
	// 새로운 Skeletal Mesh Component를 생성하여 무기 메시를 장착
	UStaticMeshComponent* WeaponMesh = NewObject<UStaticMeshComponent>(this);
	WeaponMesh->SetupAttachment(MeshComponent, TEXT("hand_rSocket"));  // hand_rSocket에 부착
	WeaponMesh->SetStaticMesh(WeaponMeshReference);
	WeaponMesh->RegisterComponent();  // 컴포넌트 등록

	// 4. 소켓 이름 확인
	FName SocketName = TEXT("hand_rSocket");
	if (!MeshComponent->DoesSocketExist(SocketName))
	{
		UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist on the mesh. Make sure the socket is correctly defined in the skeleton."), *SocketName.ToString());
		return;
	}

	// 5. 무기 소켓에 무기 부착 (위에서 생성한 WeaponMesh에 소켓 위치를 설정)
	WeaponMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

	// 6. 추가 디버깅 정보
	FTransform SocketTransform = MeshComponent->GetSocketTransform(SocketName, RTS_World);
	UE_LOG(LogTemp, Log, TEXT("Socket Transform: Location: %s, Rotation: %s"), *SocketTransform.GetLocation().ToString(), *SocketTransform.GetRotation().Rotator().ToString());

	UE_LOG(LogTemp, Log, TEXT("Weapon successfully attached to socket: %s"), *SocketName.ToString());
}
