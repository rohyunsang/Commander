// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SampleTarget.generated.h"

UCLASS()
class COMMANDER_API ASampleTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASampleTarget();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    /** ≈∏∞Ÿ¿« «ˆ¿Á HP */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target|Stats")
    float HP;

    /** ≈∏∞Ÿ¿« √÷¥Î HP */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target|Stats")
    float MaxHP;

    /** ≈∏∞Ÿ¿« ø‹«¸ (Static Mesh) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target|Visual")
    class UStaticMeshComponent* TargetMesh;

};
