// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponFireComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"


UWeaponFireComponent::UWeaponFireComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 기본값 설정
    MaxRange = 10000.f;
    BaseDamage = 20.f;
}

void UWeaponFireComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponFireComponent::Fire()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    // 액터의 시점(눈 위치와 회전)을 가져옵니다.
    FVector EyeLocation;
    FRotator EyeRotation;
    Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector ShotDirection = EyeRotation.Vector();
    FVector TraceEnd = EyeLocation + (ShotDirection * MaxRange);

    // Line Trace 수행
    FHitResult Hit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Owner);
    QueryParams.bTraceComplex = true;
    QueryParams.bReturnPhysicalMaterial = true;

    bool bHit = World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

    // 디버그 선 그리기
    DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

    if (bHit)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            // 충돌한 대상에 데미지 적용
            UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, Owner->GetInstigatorController(), Owner, nullptr);
            UE_LOG(LogTemp, Log, TEXT("WeaponFireComponent: Hit %s with damage %f"), *HitActor->GetName(), BaseDamage);
        }
    }
}