// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"

AWeaponItem::AWeaponItem()
{
    // �⺻�� ���� (�ʿ信 ���� ����)
    Damage = 25.0f;
    Range = 1000.0f;
    FireRate = 0.2f;
    MaxMagazine = 30;
    WeaponKind = EWeaponKind::Rifle;
}

void AWeaponItem::Equip()
{
    // Equip �Լ��� �⺻ ���� ����
    // ���� ���� ������ �°� ���� ����, �ִϸ��̼�, ȿ�� ���� �����ϸ� �˴ϴ�.
    UE_LOG(LogTemp, Log, TEXT("Weapon equipped: %s"), *GetName());
}
