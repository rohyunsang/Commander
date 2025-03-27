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

    // 소유한 액터에서 InventoryComponent를 찾아 저장합니다.
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

    // 지정한 범주의 아이템을 인벤토리에서 가져옵니다.
    AItem* ItemToEquip = InventoryComponent->GetItem(WeaponCategory);
    if (!ItemToEquip)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponSwapComponent: No item found for category %d on %s"),
            static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());
        return;
    }

    // 실제 무기 스왑 로직
    // 예: 기존에 장착된 무기를 교체하고, 새 무기를 캐릭터의 소켓(hand_rSocket 등)에 부착합니다.
    // 여기서는 단순히 로그로 스왑 이벤트를 확인합니다.
    UE_LOG(LogTemp, Log, TEXT("WeaponSwapComponent: Swapped to weapon of category %d on %s"),
        static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());

    // 예시: AItem 클래스에 Equip() 함수가 있다면 호출할 수 있습니다.
    // ItemToEquip->Equip();
}
