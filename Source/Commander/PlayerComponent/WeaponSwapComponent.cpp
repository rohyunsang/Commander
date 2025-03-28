// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/WeaponSwapComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Item/Item.h"
#include "Item/WeaponItem.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

UWeaponSwapComponent::UWeaponSwapComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 기본 무기 블루프린트 클래스를 로드합니다.
    LoadDefaultWeaponClasses();
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
    // SwapWeapon 함수는 단순히 로그 출력 등 스왑 이벤트를 확인하는 용도로 사용하며,
    // 실제 무기 장착은 EquipWeaponFromInventory에서 처리할 수 있습니다.
    EquipWeaponFromInventory(WeaponCategory);
    UE_LOG(LogTemp, Log, TEXT("WeaponSwapComponent: Swapped to weapon of category %d on %s"),
        static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());
}



void UWeaponSwapComponent::EquipWeaponFromInventory(EItemCategory WeaponCategory, FName SocketName)
{
    if (!InventoryComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: InventoryComponent is null."));
        return;
    }

    // InventoryComponent에서 해당 범주의 아이템을 가져옵니다.
    AItem* WeaponItem = InventoryComponent->GetItem(WeaponCategory);
    if (!WeaponItem)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipWeaponFromInventory: No weapon found for category %d on %s"),
            static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());
        return;
    }

    // 소유자의 Skeletal Mesh Component(예: 플레이어의 메쉬)를 가져옵니다.
    USkeletalMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
    if (!MeshComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: SkeletalMeshComponent not found on %s"), *GetOwner()->GetName());
        return;
    }

    // 지정된 소켓이 존재하는지 확인합니다.
    if (!MeshComponent->DoesSocketExist(SocketName))
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: Socket %s does not exist on %s"), *SocketName.ToString(), *GetOwner()->GetName());
        return;
    }

    // 기존에 소켓에 부착된 모든 컴포넌트를 제거합니다.
    TArray<USceneComponent*> AttachedComponents;
    MeshComponent->GetChildrenComponents(true, AttachedComponents);
    for (USceneComponent* ChildComp : AttachedComponents)
    {
        if (ChildComp && ChildComp->GetAttachSocketName() == SocketName)
        {
            ChildComp->DestroyComponent();
        }
    }

    // 무기 아이템의 외형(Static Mesh)을 가져옵니다.
    UStaticMesh* NewWeaponMesh = nullptr;
    if (WeaponItem->ItemMesh)
    {
        NewWeaponMesh = WeaponItem->ItemMesh->GetStaticMesh();
    }
    if (!NewWeaponMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipWeaponFromInventory: No valid weapon mesh found for item %s"), *WeaponItem->GetName());
        return;
    }

    // 새로운 Static Mesh Component를 생성하여 무기를 소켓에 부착합니다.
    UStaticMeshComponent* NewWeaponComponent = NewObject<UStaticMeshComponent>(GetOwner());
    if (!NewWeaponComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: Failed to create new weapon component."));
        return;
    }

    NewWeaponComponent->SetupAttachment(MeshComponent, SocketName);
    NewWeaponComponent->SetStaticMesh(NewWeaponMesh);
    NewWeaponComponent->RegisterComponent();

    // 추가 디버깅 로그: 소켓의 위치 및 회전 정보 출력
    FTransform SocketTransform = MeshComponent->GetSocketTransform(SocketName, RTS_World);
    UE_LOG(LogTemp, Log, TEXT("EquipWeaponFromInventory: Weapon equipped at socket %s. Location: %s, Rotation: %s"),
        *SocketName.ToString(),
        *SocketTransform.GetLocation().ToString(),
        *SocketTransform.GetRotation().Rotator().ToString());
}


void UWeaponSwapComponent::LoadDefaultWeaponClasses()
{
    // 경로는 실제 프로젝트 내 블루프린트 경로에 맞게 수정해야 합니다.
    
    // /Script/Engine.Blueprint'/Game/Blueprint/Weapon/BP_Rifle.BP_Rifle'
    // /Script/Engine.Blueprint'/Game/Blueprint/Weapon/BP_Pistol.BP_Pistol'
    // /Script/Engine.Blueprint'/Game/Blueprint/Weapon/BP_Knife.BP_Knife'

    static ConstructorHelpers::FClassFinder<AWeaponItem> PrimaryWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Rifle.BP_Rifle_C"));
    if (PrimaryWeaponBP.Succeeded())
    {
        DefaultPrimaryWeaponClass = PrimaryWeaponBP.Class;
        UE_LOG(LogTemp, Log, TEXT("DefaultPrimaryWeaponClass loaded successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultPrimaryWeaponClass."));
    }

    static ConstructorHelpers::FClassFinder<AWeaponItem> SecondaryWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Pistol.BP_Pistol_C"));
    if (SecondaryWeaponBP.Succeeded())
    {
        DefaultSecondaryWeaponClass = SecondaryWeaponBP.Class;
        UE_LOG(LogTemp, Log, TEXT("DefaultSecondaryWeaponClass loaded successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultSecondaryWeaponClass."));
    }

    static ConstructorHelpers::FClassFinder<AWeaponItem> MeleeWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Knife.BP_Knife_C"));
    if (MeleeWeaponBP.Succeeded())
    {
        DefaultMeleeWeaponClass = MeleeWeaponBP.Class;
        UE_LOG(LogTemp, Log, TEXT("DefaultMeleeWeaponClass loaded successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultMeleeWeaponClass."));
    }

    
}