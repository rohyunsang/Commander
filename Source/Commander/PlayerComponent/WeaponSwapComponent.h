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
     * 지정한 아이템 범주에 해당하는 무기로 스왑합니다.
     * 예를 들어, EItemCategory::PrimaryWeapon을 전달하면 주력 무기로 스왑합니다.
     */
    UFUNCTION(BlueprintCallable, Category = "WeaponSwap")
    void SwapWeapon(EItemCategory WeaponCategory);

private:
    // 플레이어의 InventoryComponent에 접근하기 위한 포인터
    UPROPERTY()
    UInventoryComponent* InventoryComponent;
		
};
