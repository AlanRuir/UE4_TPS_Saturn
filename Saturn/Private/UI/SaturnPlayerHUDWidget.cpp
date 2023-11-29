// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaturnPlayerHUDWidget.h"
#include "Components/SaturnHealthComponent.h"           //获取生命值组件头文件
#include "Components/SaturnWeaponComponent.h"           //获取武器组件头文件

float USaturnPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();      //获取玩家
    if (!Player) 
    {
        return 0.0f;
    }

    const auto Component = Player->GetComponentByClass(USaturnHealthComponent::StaticClass());      //获取生命值组件
    const auto HealthComponent = Cast<USaturnHealthComponent>(Component);
    if (!HealthComponent)
    {
        return 0.0f;
    }

    return HealthComponent->GetHealthPercentage();
}

bool USaturnPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();      //获取玩家
    if (!Player) 
    {
        return false;
    }

    const auto Component = Player->GetComponentByClass(USaturnWeaponComponent::StaticClass());      //获取武器组件
    const auto WeaponComponent = Cast<USaturnWeaponComponent>(Component);
    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USaturnPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto Player = GetOwningPlayerPawn();      //获取玩家
    if (!Player) 
    {
        return false;
    }

    const auto Component = Player->GetComponentByClass(USaturnWeaponComponent::StaticClass());      //获取武器组件
    const auto WeaponComponent = Cast<USaturnWeaponComponent>(Component);
    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

USaturnWeaponComponent* USaturnPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();      //获取玩家
    if (!Player) 
    {
        return nullptr;
    }

    const auto Component = Player->GetComponentByClass(USaturnWeaponComponent::StaticClass());      //获取武器组件
    return Cast<USaturnWeaponComponent>(Component);
}

bool USaturnPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetHealthComponent();
    return HealthComponent && !HealthComponent->IsDead();
}

bool USaturnPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;     //判断玩家是否是观战
}

USaturnHealthComponent* USaturnPlayerHUDWidget::GetHealthComponent() const
{
    const auto Player = GetOwningPlayerPawn();      //获取玩家
    if (!Player) 
    {
        return nullptr;
    }

    const auto Component = Player->GetComponentByClass(USaturnHealthComponent::StaticClass());      //获取生命值组件
    return Cast<USaturnHealthComponent>(Component);
}