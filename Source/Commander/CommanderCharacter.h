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

	// 무기 스왑 컴포넌트 (플레이어의 무기 스왑을 담당)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UWeaponSwapComponent* WeaponSwapComponent;

	// 인벤토리 컴포넌트 (아이템 관리)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;

	// Weapon Fire Component 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponFire")
	UWeaponFireComponent* WeaponFireComponent;

	// 무기 스왑 함수 (주력 무기로 스왑)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToPrimaryWeapon();
	
	// 무기 스왑 함수 (주력 무기로 스왑)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToSecondaryWeapon();

	// 무기 스왑 함수 (주력 무기로 스왑)
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void SwapToMeleeWeapon();

	// 무기 공격(총알 발사) 함수 
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
	// 헤더 파일에서 필요 변수 선언
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UStaticMesh* WeaponMeshReference; // 무기 메시 참조

	void EquipWeaponToHand(); // 기본 장착 무기
	
protected: 
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};

