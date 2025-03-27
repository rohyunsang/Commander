// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemCategory.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    PrimaryWeapon       UMETA(DisplayName = "Primary Weapon"),   // 샷건, 라이플, 스나이퍼 등 주력 총
    SecondaryWeapon     UMETA(DisplayName = "Secondary Weapon"), // 권총
    Melee               UMETA(DisplayName = "Melee"),
    Bomb                UMETA(DisplayName = "Bomb"),
    Hat                 UMETA(DisplayName = "Hat"),
    Shirt               UMETA(DisplayName = "Shirt"),
    Armor               UMETA(DisplayName = "Armor")
};
