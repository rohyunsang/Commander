// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Item/Item.h" 
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// �⺻ �ַ� ���� �ε� (��δ� ���� ��ο� �°� ����)
	static ConstructorHelpers::FClassFinder<AItem> PrimaryWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Rifle.BP_Rifle_C"));
	if (PrimaryWeaponBP.Succeeded())
	{
		DefaultPrimaryWeaponClass = PrimaryWeaponBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultPrimaryWeaponClass."));
	}

	// �⺻ ���� �ε�
	static ConstructorHelpers::FClassFinder<AItem> SecondaryWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Pistol.BP_Pistol_C"));
	if (SecondaryWeaponBP.Succeeded())
	{
		DefaultSecondaryWeaponClass = SecondaryWeaponBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultSecondaryWeaponClass."));
	}

	// �⺻ ���� ����(Į) �ε�
	static ConstructorHelpers::FClassFinder<AItem> MeleeWeaponBP(TEXT("/Game/Blueprint/Weapon/BP_Knife.BP_Knife_C"));
	if (MeleeWeaponBP.Succeeded())
	{
		DefaultMeleeWeaponClass = MeleeWeaponBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load DefaultMeleeWeaponClass."));
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// �⺻ �����۵��� �ʱ�ȭ�մϴ�.
	InitializeDefaults();
}

void UInventoryComponent::InitializeDefaults()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	// �⺻ �ַ� ���� ���� �� �߰�
	if (DefaultPrimaryWeaponClass)
	{
		AItem* PrimaryWeapon = World->SpawnActor<AItem>(DefaultPrimaryWeaponClass);
		AddOrReplaceItem(EItemCategory::PrimaryWeapon, PrimaryWeapon);
	}

	// �⺻ ���� ���� �� �߰�
	if (DefaultSecondaryWeaponClass)
	{
		AItem* SecondaryWeapon = World->SpawnActor<AItem>(DefaultSecondaryWeaponClass);
		AddOrReplaceItem(EItemCategory::SecondaryWeapon, SecondaryWeapon);
	}

	// �⺻ ���� ����(Į) ���� �� �߰�
	if (DefaultMeleeWeaponClass)
	{
		AItem* MeleeWeapon = World->SpawnActor<AItem>(DefaultMeleeWeaponClass);
		AddOrReplaceItem(EItemCategory::Melee, MeleeWeapon);
	}
	
}

void UInventoryComponent::AddOrReplaceItem(EItemCategory Category, AItem* NewItem)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddOrReplaceItem: NewItem is null."));
		return;
	}

	// ���� �������� �ִٸ� �����մϴ�.
	if (Items.Contains(Category) && Items[Category] != nullptr)
	{
		AItem* ExistingItem = Items[Category];
		if (ExistingItem)
		{
			UE_LOG(LogTemp, Log, TEXT("Replacing existing item in category %d on %s"), static_cast<uint8>(Category), *GetOwner()->GetName());
			ExistingItem->Destroy();
		}
	}

	Items.Add(Category, NewItem);
	UE_LOG(LogTemp, Log, TEXT("Added item to category %d on %s"), static_cast<uint8>(Category), *GetOwner()->GetName());
}

AItem* UInventoryComponent::GetItem(EItemCategory Category) const
{
	if (Items.Contains(Category))
	{
		return Items[Category];
	}
	return nullptr;
}