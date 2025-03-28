// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDER_API UWeaponFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponFireComponent();

protected:
    virtual void BeginPlay() override;

public:
    /**
     * 총 발사 함수 (Hitscan 방식)
     * 액터의 Eyes 위치에서 바라보는 방향으로 선형 트레이스를 수행하여 충돌한 대상에 데미지를 적용합니다.
     */
    UFUNCTION(BlueprintCallable, Category = "WeaponFire")
    void Fire();

    /** 최대 발사 사거리 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponFire")
    float MaxRange;

    /** 기본 데미지 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponFire")
    float BaseDamage;

		
};
