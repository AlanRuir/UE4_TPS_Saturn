// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/SaturnDevDamageActor.h"
#include "DrawDebugHelpers.h"       //用于调试的绘制组件头文件
#include "Kismet/GameplayStatics.h"     //用于游戏中的静态函数头文件，里面有很多静态函数，包括ApplyRadialDamage

// Sets default values
ASaturnDevDamageActor::ASaturnDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);       //设置根组件为SceneComponent
}

// Called when the game starts or when spawned
void ASaturnDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaturnDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);      //应用半径为Radius的伤害
}

