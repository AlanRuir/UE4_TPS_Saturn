// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/AWeaponBase.h"
#include "Weapon/SaturnProjectile.h"		//子弹类头文件
#include "Kismet/GameplayStatics.h"			//静态函数头文件
#include "SaturnLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API ASaturnLauncherWeapon : public AAWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;

protected:
	virtual void MakeShot() override;
protected:
	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<class ASaturnProjectile> ProjectileClass;		//子弹类
};
