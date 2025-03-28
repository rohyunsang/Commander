// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CommanderCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class UInventoryComponent;
class UWeaponSwapComponent;
class UWeaponFireComponent;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACommanderCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapPrimaryAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapSecondaryAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapMeleeAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponFireAction;

public:
	ACommanderCharacter();

	// ���� ���� ������Ʈ (�÷��̾��� ���� ������ ���)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UWeaponSwapComponent* WeaponSwapComponent;

	// �κ��丮 ������Ʈ (������ ����)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;

	// Weapon Fire Component 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponFire")
	UWeaponFireComponent* WeaponFireComponent;

	// ���� ���� �Լ� (�ַ� ����� ����)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToPrimaryWeapon();
	
	// ���� ���� �Լ� (�ַ� ����� ����)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToSecondaryWeapon();

	// ���� ���� �Լ� (�ַ� ����� ����)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToMeleeWeapon();

	// ���� ����(�Ѿ� �߻�) �Լ� 
	UFUNCTION(BlueprintCallable, Category = "WeaponFire")
	void WeaponFire();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



public: 
	// ��� ���Ͽ��� �ʿ� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UStaticMesh* WeaponMeshReference; // ���� �޽� ����

	void EquipWeaponToHand(); // �⺻ ���� ����
	
protected: 
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};

