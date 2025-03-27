// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemCategory.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    PrimaryWeapon       UMETA(DisplayName = "Primary Weapon"),   // ����, ������, �������� �� �ַ� ��
    SecondaryWeapon     UMETA(DisplayName = "Secondary Weapon"), // ����
    Melee               UMETA(DisplayName = "Melee"),
    Bomb                UMETA(DisplayName = "Bomb"),
    Hat                 UMETA(DisplayName = "Hat"),
    Shirt               UMETA(DisplayName = "Shirt"),
    Armor               UMETA(DisplayName = "Armor")
};
