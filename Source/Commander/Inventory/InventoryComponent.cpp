// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Item/Item.h" 
#include "Engine/World.h"
#include "GameFramework/Actor.h"



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 기본 아이템들을 초기화합니다.
	InitializeDefaults();
}

void UInventoryComponent::InitializeDefaults()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// 기본 주력 무기 스폰 및 추가
	if (DefaultPrimaryWeaponClass)
	{
		AItem* PrimaryWeapon = World->SpawnActor<AItem>(DefaultPrimaryWeaponClass);
		AddOrReplaceItem(EItemCategory::PrimaryWeapon, PrimaryWeapon);
	}

	// 기본 권총 스폰 및 추가
	if (DefaultSecondaryWeaponClass)
	{
		AItem* SecondaryWeapon = World->SpawnActor<AItem>(DefaultSecondaryWeaponClass);
		AddOrReplaceItem(EItemCategory::SecondaryWeapon, SecondaryWeapon);
	}

	// 기본 근접 무기(칼) 스폰 및 추가
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

	// 기존 아이템이 있다면 제거합니다.
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