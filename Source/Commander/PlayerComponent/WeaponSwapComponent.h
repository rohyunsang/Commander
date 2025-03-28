// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/EItemCategory.h"
#include "WeaponSwapComponent.generated.h"


class UInventoryComponent;
class AItem;
class AWeaponItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDER_API UWeaponSwapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSwapComponent();

protected:
    virtual void BeginPlay() override;

public:
    /**
     * ������ ������ ���ֿ� �ش��ϴ� ����� �����մϴ�.
     * ���� ���, EItemCategory::PrimaryWeapon�� �����ϸ� �ַ� ����� �����մϴ�.
     */
    UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
    void SwapWeapon(EItemCategory WeaponCategory);

	/**
	 * InventoryComponent�� ��ϵ� ���⸦ ������ ���Ͽ� �����մϴ�.
	 * ���� ���Ͽ� ������ ����� �����ϰ� �� ���⸦ �����մϴ�.
	 *
	 * @param WeaponCategory ���� ���� (��: PrimaryWeapon, SecondaryWeapon, Melee)
	 * @param SocketName ������ ���� �̸� (�⺻��: "hand_rSocket")
	 */
	UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
	void EquipWeaponFromInventory(EItemCategory WeaponCategory, FName SocketName = TEXT("hand_rSocket"));

	/**
	 * ConstructorHelpers�� �̿��� �⺻ ���� �������Ʈ Ŭ������ �ε��մϴ�.
	 * (���ÿ� �Լ��̸�, �����ڿ��� �ڵ����� ȣ���մϴ�.)
	 */
	void LoadDefaultWeaponClasses();

	/** �⺻ �ַ� ���� �������Ʈ Ŭ���� (ConstructorHelpers�� �ε�) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultPrimaryWeaponClass;

	/** �⺻ ���� �������Ʈ Ŭ���� (ConstructorHelpers�� �ε�) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultSecondaryWeaponClass;

	/** �⺻ ���� ����(Į) �������Ʈ Ŭ���� (ConstructorHelpers�� �ε�) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSwap|Defaults")
	TSubclassOf<AItem> DefaultMeleeWeaponClass;


private:
    // �÷��̾��� InventoryComponent�� �����ϱ� ���� ������
    UPROPERTY()
    UInventoryComponent* InventoryComponent;
		
};
