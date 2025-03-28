// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponFireComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"


UWeaponFireComponent::UWeaponFireComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // �⺻�� ����
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

    // ������ ����(�� ��ġ�� ȸ��)�� �����ɴϴ�.
    FVector EyeLocation;
    FRotator EyeRotation;
    Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector ShotDirection = EyeRotation.Vector();
    FVector TraceEnd = EyeLocation + (ShotDirection * MaxRange);

    // Line Trace ����
    FHitResult Hit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Owner);
    QueryParams.bTraceComplex = true;
    QueryParams.bReturnPhysicalMaterial = true;

    bool bHit = World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

    // ����� �� �׸���
    DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

    if (bHit)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            // �浹�� ��� ������ ����
            UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, Owner->GetInstigatorController(), Owner, nullptr);
            UE_LOG(LogTemp, Log, TEXT("WeaponFireComponent: Hit %s with damage %f"), *HitActor->GetName(), BaseDamage);
        }
    }
}