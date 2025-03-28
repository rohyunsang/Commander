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

    // �⺻ HP �� ����
    MaxHP = 100.0f;
    HP = MaxHP;

    // Static Mesh Component ���� �� ��Ʈ ������Ʈ�� ����
    TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
    RootComponent = TargetMesh;
}

void ASampleTarget::BeginPlay()
{
    Super::BeginPlay();

    // �ʱ�ȭ �Ǵ� ����� ���
    UE_LOG(LogTemp, Log, TEXT("ASampleTarget '%s' spawned with HP: %f"), *GetName(), HP);
}

void ASampleTarget::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float ASampleTarget::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// �⺻������ ������ ���� ������ ������ ���� ���� (�⺻ ������ "Body")
	FName HitPart = TEXT("Body");

	// ������ ������ ����
	float FinalDamage = Damage;
	if (HitPart == TEXT("Head"))
	{
		FinalDamage *= 2.0f;  // ��弦�� 2�� ������
	}
	else if (HitPart == TEXT("Leg"))
	{
		FinalDamage *= 0.75f; // �ٸ� ������ 75% ������
	}
	// "Body"�� ��쿡�� �⺻ �������� �����մϴ�.

	// HP ����
	HP -= FinalDamage;
	UE_LOG(LogTemp, Log, TEXT("%s hit at %s, Damage: %f, Remaining HP: %f"), *GetName(), *HitPart.ToString(), FinalDamage, HP);

	// HP�� 0 �����̸� ���͸� �ı�
	if (HP <= 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("%s is destroyed."), *GetName());
		Destroy();
	}

	// ���� ����� ������ ��ȯ (���� �ٸ� �ý��۰� ���� �� ���� �� ����)
	return FinalDamage;
}