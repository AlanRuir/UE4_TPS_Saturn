// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SaturnPickupBase.h"

ASaturnPickupBase::ASaturnPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(50.0f);		//设置碰撞半径
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);		//设置碰撞类型为警告
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);		//设置所有通道为重叠
	SetRootComponent(CollisionComponent);			//设置根组件为碰撞组件
}

void ASaturnPickupBase::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);				//检查碰撞组件
	GenerateRotationYaw();					//设置旋转角度
}

void ASaturnPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));		//旋转
}

void ASaturnPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
    {
        return;
    }

	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();		//拾取
	}
}

void ASaturnPickupBase::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);		//设置所有通道为忽略
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);		//设置可见性为false
	}
	
	FTimerHandle RespawnTimerHandle;		//创建定时器句柄
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASaturnPickupBase::Respawn, RespawnTime);
}

void ASaturnPickupBase::Respawn()
{
	GenerateRotationYaw();					//设置旋转角度
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);		//设置所有通道为重叠
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);		//设置可见性为true
	}
}

bool ASaturnPickupBase::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASaturnPickupBase::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}