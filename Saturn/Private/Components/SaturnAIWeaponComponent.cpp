// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SaturnAIWeaponComponent.h"
#include "Weapon/AWeaponBase.h"

void USaturnAIWeaponComponent::StartFire()
{
    if (!CanFire())
    {
        return;
    }

    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USaturnAIWeaponComponent::NextWeapon()
{
    if (!CanEquip())
    {
        return;
    }

    int32 NextIndex = (CurrentWeaponIndex + 1) % WeaponData.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty())
        {
            break;
        }
        NextIndex = (NextIndex + 1) % WeaponData.Num();
    }

    if (NextIndex != CurrentWeaponIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}