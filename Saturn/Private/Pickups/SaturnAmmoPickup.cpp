// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SaturnAmmoPickup.h"

bool ASaturnAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = Cast<USaturnHealthComponent>(PlayerPawn->GetComponentByClass(USaturnHealthComponent::StaticClass()));      //获取生命值组件
    if (!HealthComponent || HealthComponent->IsDead())
    {
        return false;
    }

    const auto WeaponComponent = Cast<USaturnWeaponComponent>(PlayerPawn->GetComponentByClass(USaturnWeaponComponent::StaticClass()));      //获取武器组件
    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);        //尝试添加弹药
}