// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EWeaponType.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Primary     UMETA(DisplayName = "Primary"),
    Secondary   UMETA(DisplayName = "Secondary"),
    Melee       UMETA(DisplayName = "Melee")
};

