// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaturnDevDamageActor.generated.h"

UCLASS()
class SATURN_API ASaturnDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaturnDevDamageActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;        //基础组件，给WuKongDevDamageActor赋予转换和移动的能力
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;                  //半径
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;       //颜色
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;                   //伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;              //是否应用完全伤害

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
