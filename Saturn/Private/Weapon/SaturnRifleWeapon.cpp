// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SaturnRifleWeapon.h"

ASaturnRifleWeapon::ASaturnRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USaturnWeaponFXComponent>("WeaponFXComponent");
}

void ASaturnRifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASaturnRifleWeapon::StartFire()
{
	MakeShot();
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ASaturnRifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASaturnRifleWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}

void ASaturnRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	const auto Player = Cast<ACharacter>(GetOwner());		//获取拥有者，即为玩家
	if (!Player)
	{
		StopFire();
		return;
	}

	const auto Controller = Player->GetController<AController>();		//获取控制器
	if (!Controller)
	{
		StopFire();
		return;
	}

	PlayFireSound();
	FVector ViewLocation;		//视角位置
	FRotator ViewRotation;		//视角方向
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);		//获取视角位置和方向

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);		//获取枪口
	const FVector TraceStart = ViewLocation; //SocketTransform.GetLocation();					//获取发射位置
	// const FVector ShootDirection = ViewRotation.Vector();//SocketTransform.GetRotation().Vector();		//获取发射方向
	const auto HalfRadius = FMath::DegreesToRadians(BulletSpread);		//获取扩散半径
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRadius);		//获取带有后坐力的发射方向
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;	//获取发射结束位置

	FCollisionQueryParams CollisionParams;		//创建碰撞检测参数
	CollisionParams.AddIgnoredActor(GetOwner());	//忽略拥有者
	CollisionParams.bReturnPhysicalMaterial = true;		//返回物理材质

	FHitResult HitResult;		//它是一个表示碰撞点的结构体，里面包含碰撞点的位置、法向量、是否被碰撞、碰撞点的碰撞体等信息

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);	//在发射位置和发射结束位置之间检测是否有障碍物
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);		//创建伤害
		// DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);						//画发射轨迹线
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);				//在障碍物点画球
		WeaponFXComponent->PlayImpactFX(HitResult);		//播放子弹碰撞特效
	}
	else
	{
		// DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);						//画发射轨迹线
	}

	DecreaseAmmo();
}

