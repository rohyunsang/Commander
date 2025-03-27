// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/WeaponSwapComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Item/Item.h"
#include "GameFramework/Actor.h"

UWeaponSwapComponent::UWeaponSwapComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponSwapComponent::BeginPlay()
{
    Super::BeginPlay();

    // ������ ���Ϳ��� InventoryComponent�� ã�� �����մϴ�.
    InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!InventoryComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponSwapComponent: InventoryComponent not found on %s"), *GetOwner()->GetName());
    }
}

void UWeaponSwapComponent::SwapWeapon(EItemCategory WeaponCategory)
{
    if (!InventoryComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponSwapComponent: Cannot swap weapon, InventoryComponent is null."));
        return;
    }

    // ������ ������ �������� �κ��丮���� �����ɴϴ�.
    AItem* ItemToEquip = InventoryComponent->GetItem(WeaponCategory);
    if (!ItemToEquip)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponSwapComponent: No item found for category %d on %s"),
            static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());
        return;
    }

    // ���� ���� ���� ����
    // ��: ������ ������ ���⸦ ��ü�ϰ�, �� ���⸦ ĳ������ ����(hand_rSocket ��)�� �����մϴ�.
    // ���⼭�� �ܼ��� �α׷� ���� �̺�Ʈ�� Ȯ���մϴ�.
    UE_LOG(LogTemp, Log, TEXT("WeaponSwapComponent: Swapped to weapon of category %d on %s"),
        static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());

    // ����: AItem Ŭ������ Equip() �Լ��� �ִٸ� ȣ���� �� �ֽ��ϴ�.
    // ItemToEquip->Equip();
}
