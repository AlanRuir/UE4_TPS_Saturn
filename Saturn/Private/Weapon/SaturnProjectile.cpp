// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SaturnProjectile.h"

ASaturnProjectile::ASaturnProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);		//设置碰撞半径
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);		//设置碰撞类型为警告
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);		//设置所有通道为阻挡
	CollisionComponent->bReturnMaterialOnMove = true;		//设置返回材质
	SetRootComponent(CollisionComponent);			//设置根组件为碰撞组件
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));		//设置子弹移动组件
	ProjectileMovementComponent->InitialSpeed = 2000.0f;		//设置初始速度
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;		//设置重力

	WeaponFXComponent = CreateDefaultSubobject<USaturnWeaponFXComponent>("WeaponFXComponent");		//设置子弹碰撞特效
}

void ASaturnProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(ProjectileMovementComponent);
	check(WeaponFXComponent);
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;		//设置子弹速度
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);		//忽略拥有者(防止炸死自己)
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASaturnProjectile::OnProjectileHit);		//添加碰撞回调
	SetLifeSpan(LifeSeconds);		//设置生命期
}

void ASaturnProjectile::SetShotDirection(const FVector& Direction)
{
	ShotDirection = Direction;
}

void ASaturnProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())
	{
		return;
	}

	ProjectileMovementComponent->StopMovementImmediately();		//停止移动
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFullDamage);		//产生径向伤害

	// DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);		//绘制半径为Radius的伤害
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();				//销毁
}

AController* ASaturnProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());		//获取拥有者
	return Pawn ? Pawn->GetController<APlayerController>() : nullptr;
}