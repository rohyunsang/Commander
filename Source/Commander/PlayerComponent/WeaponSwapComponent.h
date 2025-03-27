// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/EItemCategory.h"
#include "WeaponSwapComponent.generated.h"


class UInventoryComponent;
class AItem;

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

private:
    // �÷��̾��� InventoryComponent�� �����ϱ� ���� ������
    UPROPERTY()
    UInventoryComponent* InventoryComponent;
		
};
