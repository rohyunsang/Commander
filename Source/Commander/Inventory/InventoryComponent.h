// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/EItemCategory.h"
#include "InventoryComponent.generated.h"

class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** 각 아이템 범주별로 한 개씩 보유 (나중에 필요하면 여러 개로 확장 가능) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EItemCategory, AItem*> Items;

	/** 에디터에서 기본 주력 무기(Primary Weapon) 클래스 지정 (예: 라이플, 샷건 등) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultPrimaryWeaponClass;

	/** 에디터에서 기본 권총(Secondary Weapon) 클래스 지정 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultSecondaryWeaponClass;

	/** 에디터에서 기본 근접 무기(Melee) 클래스 지정 (예: 칼) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultMeleeWeaponClass;

	/**
	 * 기본 아이템들을 인벤토리에 초기화합니다.
	 * 게임 시작 시 BeginPlay에서 호출되어 기본 무기들을 스폰하고 추가합니다.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeDefaults();

	/**
	 * 지정한 범주의 아이템을 추가하거나 교체합니다.
	 * 기존 아이템이 있으면 제거(Destroy)하고 새 아이템으로 대체합니다.
	 *
	 * @param Category 추가할 아이템의 범주
	 * @param NewItem  추가할 새 아이템
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddOrReplaceItem(EItemCategory Category, AItem* NewItem);

	/**
	 * 지정한 범주의 아이템을 반환합니다.
	 *
	 * @param Category 검색할 아이템 범주
	 * @return 해당 범주의 아이템, 없으면 nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItem(EItemCategory Category) const;
};