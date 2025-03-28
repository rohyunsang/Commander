// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"

AWeaponItem::AWeaponItem()
{
    // 기본값 설정 (필요에 따라 수정)
    Damage = 25.0f;
    Range = 1000.0f;
    FireRate = 0.2f;
    MaxMagazine = 30;
    WeaponKind = EWeaponKind::Rifle;
}

void AWeaponItem::Equip()
{
    // Equip 함수의 기본 구현 예시
    // 실제 게임 로직에 맞게 무기 부착, 애니메이션, 효과 등을 구현하면 됩니다.
    UE_LOG(LogTemp, Log, TEXT("Weapon equipped: %s"), *GetName());
}
