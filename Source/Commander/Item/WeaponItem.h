// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "WeaponItem.generated.h"


/** ���� ������ ��Ÿ���� enum */
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

    /** ���� ������ */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float Damage;

    /** ���� ��Ÿ� */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float Range;

    /** ���� �߻� �ӵ� (�߻� ����) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    float FireRate;

    /** ������ �ִ� źâ ũ�� */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    int32 MaxMagazine;

    /** ������ ���� (Sniper, Rifle, Shotgun, Pistol) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    EWeaponKind WeaponKind;

    /**
     * ���⸦ �����ϴ� �Լ�
     * ������ ���⸦ ĳ������ ���Ͽ� �����ϰų� �ִϸ��̼� ��ȯ ���� ������ ������ �� �ֽ��ϴ�.
     */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void Equip();
};
