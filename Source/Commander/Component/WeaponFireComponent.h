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
     * �� �߻� �Լ� (Hitscan ���)
     * ������ Eyes ��ġ���� �ٶ󺸴� �������� ���� Ʈ���̽��� �����Ͽ� �浹�� ��� �������� �����մϴ�.
     */
    UFUNCTION(BlueprintCallable, Category = "WeaponFire")
    void Fire();

    /** �ִ� �߻� ��Ÿ� */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponFire")
    float MaxRange;

    /** �⺻ ������ */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponFire")
    float BaseDamage;

		
};
