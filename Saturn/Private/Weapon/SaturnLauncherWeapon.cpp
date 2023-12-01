// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SaturnLauncherWeapon.h"

void ASaturnLauncherWeapon::StartFire()
{
    MakeShot();
}

void ASaturnLauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
	{
		return;
	}

	const auto Player = Cast<ACharacter>(GetOwner());		//获取拥有者，即为玩家
	if (!Player)
	{
		return;
	}

	const auto Controller = Player->GetController<AController>();		//获取控制器
	if (!Controller)
	{
		return;
	}

	FVector ViewLocation;		//视角位置
	FRotator ViewRotation;		//视角方向
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);		//获取视角位置和方向

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);		//获取枪口
	const FVector TraceStart = ViewLocation; //SocketTransform.GetLocation();					//获取发射位置
	const FVector ShootDirection = ViewRotation.Vector();//SocketTransform.GetRotation().Vector();		//获取发射方向
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;	//获取发射结束位置

	FCollisionQueryParams CollisionParams;		//创建碰撞检测参数
	CollisionParams.AddIgnoredActor(GetOwner());	//忽略拥有者
	CollisionParams.bReturnPhysicalMaterial = true;		//返回物理材质

	FHitResult HitResult;		//它是一个表示碰撞点的结构体，里面包含碰撞点的位置、法向量、是否被碰撞、碰撞点的碰撞体等信息

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);	//在发射位置和发射结束位置之间检测是否有障碍物

    const FVector Endpoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;     //获取碰撞点
    const FVector Direction = (Endpoint - SocketTransform.GetLocation()).GetSafeNormal();     //获取发射方向

    const FTransform SpawnTransform(FRotator::ZeroRotator, SocketTransform.GetLocation());        //获取枪口位置
    // auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);      //创建子弹
    ASaturnProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASaturnProjectile>(ProjectileClass, SpawnTransform);      //创建子弹(重写)
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);      //设置子弹方向
		Projectile->SetOwner(GetOwner());			  //设置拥有者
        Projectile->FinishSpawning(SpawnTransform);      //结束生成子弹
    }
    //设置子弹参数
    // UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);      //结束生成子弹

	DecreaseAmmo();
}