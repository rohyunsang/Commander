// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "WeaponItem.generated.h"


/** 무기 종류를 나타내는 enum */
UENUM(BlueprintType)
enum class EWeaponKind : uint8
{
    Sniper      UMETA(DisplayName = "Sniper"),
    Rifle       UMETA(DisplayName = "Rifle"),
    Shotgun     UMETA(DisplayName = "Shotgun"),
    Pistol      UMETA(DisplayName = "Pistol")
};



/**
 * 
 */
UCLASS()
class COMMANDER_API AWeaponItem : public AItem
{
	GENERATED_BODY()

public:
    AWeaponItem();

    /** 무기 데미지 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float Damage;

    /** 무기 사거리 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float Range;

    /** 무기 발사 속도 (발사 간격) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float FireRate;

    /** 무기의 최대 탄창 크기 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    int32 MaxMagazine;

    /** 무기의 종류 (Sniper, Rifle, Shotgun, Pistol) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    EWeaponKind WeaponKind;

    /**
     * 무기를 장착하는 함수
     * 실제로 무기를 캐릭터의 소켓에 부착하거나 애니메이션 전환 등의 로직을 구현할 수 있습니다.
     */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void Equip();
};
