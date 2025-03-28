// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/EItemCategory.h"
#include "WeaponSwapComponent.generated.h"


class UInventoryComponent;
class AItem;
class AWeaponItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDER_API UWeaponSwapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSwapComponent();

protected:
    virtual void BeginPlay() override;

public:
    /**
     * 지정한 아이템 범주에 해당하는 무기로 스왑합니다.
     * 예를 들어, EItemCategory::PrimaryWeapon을 전달하면 주력 무기로 스왑합니다.
     */
    UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
    void SwapWeapon(EItemCategory WeaponCategory);

	/**
	 * InventoryComponent에 등록된 무기를 지정된 소켓에 장착합니다.
	 * 기존 소켓에 부착된 무기는 제거하고 새 무기를 부착합니다.
	 *
	 * @param WeaponCategory 무기 범주 (예: PrimaryWeapon, SecondaryWeapon, Melee)
	 * @param SocketName 장착할 소켓 이름 (기본값: "hand_rSocket")
	 */
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void EquipWeaponFromInventory(EItemCategory WeaponCategory, FName SocketName = TEXT("hand_rSocket"));

	/**
	 * ConstructorHelpers를 이용해 기본 무기 블루프린트 클래스를 로드합니다.
	 * (예시용 함수이며, 생성자에서 자동으로 호출합니다.)
	 */
	void LoadDefaultWeaponClasses();

	/** 기본 주력 무기 블루프린트 클래스 (ConstructorHelpers로 로드) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultPrimaryWeaponClass;

	/** 기본 권총 블루프린트 클래스 (ConstructorHelpers로 로드) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultSecondaryWeaponClass;

	/** 기본 근접 무기(칼) 블루프린트 클래스 (ConstructorHelpers로 로드) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultMeleeWeaponClass;


private:
    // 플레이어의 InventoryComponent에 접근하기 위한 포인터
    UPROPERTY()
    UInventoryComponent* InventoryComponent;
		
};
