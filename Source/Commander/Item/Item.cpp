// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Static Mesh Component 생성 및 초기화
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	// ItemMesh를 루트 컴포넌트로 설정 (필요에 따라 다른 컴포넌트 계층 구조를 구성할 수 있습니다)
	RootComponent = ItemMesh;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

