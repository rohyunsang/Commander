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

    // �⺻ ���� �������Ʈ Ŭ������ �ε��մϴ�.
    LoadDefaultWeaponClasses();
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
    // SwapWeapon �Լ��� �ܼ��� �α� ��� �� ���� �̺�Ʈ�� Ȯ���ϴ� �뵵�� ����ϸ�,
    // ���� ���� ������ EquipWeaponFromInventory���� ó���� �� �ֽ��ϴ�.
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

    // InventoryComponent���� �ش� ������ �������� �����ɴϴ�.
    AItem* WeaponItem = InventoryComponent->GetItem(WeaponCategory);
    if (!WeaponItem)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipWeaponFromInventory: No weapon found for category %d on %s"),
            static_cast<uint8>(WeaponCategory), *GetOwner()->GetName());
        return;
    }

    // �������� Skeletal Mesh Component(��: �÷��̾��� �޽�)�� �����ɴϴ�.
    USkeletalMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
    if (!MeshComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: SkeletalMeshComponent not found on %s"), *GetOwner()->GetName());
        return;
    }

    // ������ ������ �����ϴ��� Ȯ���մϴ�.
    if (!MeshComponent->DoesSocketExist(SocketName))
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: Socket %s does not exist on %s"), *SocketName.ToString(), *GetOwner()->GetName());
        return;
    }

    // ������ ���Ͽ� ������ ��� ������Ʈ�� �����մϴ�.
    TArray<USceneComponent*> AttachedComponents;
    MeshComponent->GetChildrenComponents(true, AttachedComponents);
    for (USceneComponent* ChildComp : AttachedComponents)
    {
        if (ChildComp && ChildComp->GetAttachSocketName() == SocketName)
        {
            ChildComp->DestroyComponent();
        }
    }

    // ���� �������� ����(Static Mesh)�� �����ɴϴ�.
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

    // ���ο� Static Mesh Component�� �����Ͽ� ���⸦ ���Ͽ� �����մϴ�.
    UStaticMeshComponent* NewWeaponComponent = NewObject<UStaticMeshComponent>(GetOwner());
    if (!NewWeaponComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeaponFromInventory: Failed to create new weapon component."));
        return;
    }

    NewWeaponComponent->SetupAttachment(MeshComponent, SocketName);
    NewWeaponComponent->SetStaticMesh(NewWeaponMesh);
    NewWeaponComponent->RegisterComponent();

    // �߰� ����� �α�: ������ ��ġ �� ȸ�� ���� ���
    FTransform SocketTransform = MeshComponent->GetSocketTransform(SocketName, RTS_World);
    UE_LOG(LogTemp, Log, TEXT("EquipWeaponFromInventory: Weapon equipped at socket %s. Location: %s, Rotation: %s"),
        *SocketName.ToString(),
        *SocketTransform.GetLocation().ToString(),
        *SocketTransform.GetRotation().Rotator().ToString());
}


void UWeaponSwapComponent::LoadDefaultWeaponClasses()
{
    // ��δ� ���� ������Ʈ �� �������Ʈ ��ο� �°� �����ؾ� �մϴ�.
    
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