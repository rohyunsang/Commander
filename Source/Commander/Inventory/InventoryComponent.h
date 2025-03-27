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
	/** �� ������ ���ֺ��� �� ���� ���� (���߿� �ʿ��ϸ� ���� ���� Ȯ�� ����) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EItemCategory, AItem*> Items;

	/** �����Ϳ��� �⺻ �ַ� ����(Primary Weapon) Ŭ���� ���� (��: ������, ���� ��) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultPrimaryWeaponClass;

	/** �����Ϳ��� �⺻ ����(Secondary Weapon) Ŭ���� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultSecondaryWeaponClass;

	/** �����Ϳ��� �⺻ ���� ����(Melee) Ŭ���� ���� (��: Į) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Defaults")
	TSubclassOf<AItem> DefaultMeleeWeaponClass;

	/**
	 * �⺻ �����۵��� �κ��丮�� �ʱ�ȭ�մϴ�.
	 * ���� ���� �� BeginPlay���� ȣ��Ǿ� �⺻ ������� �����ϰ� �߰��մϴ�.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeDefaults();

	/**
	 * ������ ������ �������� �߰��ϰų� ��ü�մϴ�.
	 * ���� �������� ������ ����(Destroy)�ϰ� �� ���������� ��ü�մϴ�.
	 *
	 * @param Category �߰��� �������� ����
	 * @param NewItem  �߰��� �� ������
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddOrReplaceItem(EItemCategory Category, AItem* NewItem);

	/**
	 * ������ ������ �������� ��ȯ�մϴ�.
	 *
	 * @param Category �˻��� ������ ����
	 * @return �ش� ������ ������, ������ nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItem(EItemCategory Category) const;
};