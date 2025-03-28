// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SampleTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

ASampleTarget::ASampleTarget()
{
    PrimaryActorTick.bCanEverTick = true;

    // 기본 HP 값 설정
    MaxHP = 100.0f;
    HP = MaxHP;

    // Static Mesh Component 생성 및 루트 컴포넌트로 설정
    TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
    RootComponent = TargetMesh;
}

void ASampleTarget::BeginPlay()
{
    Super::BeginPlay();

    // 초기화 또는 디버그 출력
    UE_LOG(LogTemp, Log, TEXT("ASampleTarget '%s' spawned with HP: %f"), *GetName(), HP);
}

void ASampleTarget::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float ASampleTarget::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 기본적으로 부위에 따른 데미지 조정을 위한 변수 (기본 부위는 "Body")
	FName HitPart = TEXT("Body");

	// 부위별 데미지 보정
	float FinalDamage = Damage;
	if (HitPart == TEXT("Head"))
	{
		FinalDamage *= 2.0f;  // 헤드샷은 2배 데미지
	}
	else if (HitPart == TEXT("Leg"))
	{
		FinalDamage *= 0.75f; // 다리 부위는 75% 데미지
	}
	// "Body"의 경우에는 기본 데미지를 적용합니다.

	// HP 감소
	HP -= FinalDamage;
	UE_LOG(LogTemp, Log, TEXT("%s hit at %s, Damage: %f, Remaining HP: %f"), *GetName(), *HitPart.ToString(), FinalDamage, HP);

	// HP가 0 이하이면 액터를 파괴
	if (HP <= 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("%s is destroyed."), *GetName());
		Destroy();
	}

	// 실제 적용된 데미지 반환 (추후 다른 시스템과 연동 시 사용될 수 있음)
	return FinalDamage;
}