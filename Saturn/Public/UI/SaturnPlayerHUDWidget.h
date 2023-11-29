// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/AWeaponBase.h"
#include "Components/SaturnWeaponComponent.h"
#include "Components/SaturnHealthComponent.h"		//获取生命值组件头文件
#include "SaturnPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API USaturnPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;		//获取武器UI信息
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;		//获取子弹信息
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;								//判断玩家是否存活
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;						//判断玩家是否是观战
private:
	USaturnWeaponComponent* GetWeaponComponent() const;		//获取武器组件
	USaturnHealthComponent* GetHealthComponent() const;		//获取生命值组件
};
