// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AWeaponBase.h"

AAWeaponBase::AAWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;		//将bCanEverTick置为false

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);				//设置WeaponMesh为根组件
}

void AAWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	CurrentAmmo = DefaultAmmo;		//初始化弹匣为默认弹匣
}

void AAWeaponBase::StartFire()
{
	
}

void AAWeaponBase::StopFire()
{
	
}

void AAWeaponBase::MakeShot()
{
	
}

void AAWeaponBase::MakeDamage(const FHitResult& HitResult)
{
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

	const auto DamagedActor = HitResult.GetActor();		//获取被击中的对象
	if (!DamagedActor)
	{
		return;
	}

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, this);		//扣血
}

void AAWeaponBase::DecreaseAmmo()
{
	--CurrentAmmo.Bullets;
	// LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		ChangeClip();
	}
}

bool AAWeaponBase::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AAWeaponBase::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void AAWeaponBase::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if (!CurrentAmmo.Infinite)
	{
		--CurrentAmmo.Clips;
	}
	UE_LOG(LogTemp, Display, TEXT("Clip changed"));
}

void AAWeaponBase::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? " Infinite" : FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}

FWeaponUIData AAWeaponBase::GetUIData() const
{
	return UIData;
}

FAmmoData AAWeaponBase::GetAmmoData() const
{
	return CurrentAmmo;
}

bool AAWeaponBase::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool AAWeaponBase::TryToAddAmmo(int32 ClipsAmount)
{
	if (IsAmmoFull() || CurrentAmmo.Infinite || ClipsAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ammo"));
		return false;
	}
	
	if (IsAmmoEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ammo was empty"));
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		// OnClipEmpty.Broadcast();
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (NextClipsAmount > DefaultAmmo.Clips)
		{
			UE_LOG(LogTemp, Warning, TEXT("Clips were full"));
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Clips were not full"));
			CurrentAmmo.Clips = NextClipsAmount;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Clips were full"));
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}

	return true;
}

