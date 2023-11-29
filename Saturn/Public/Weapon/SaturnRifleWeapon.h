// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/AWeaponBase.h"
#include "Weapon/SaturnWeaponFXComponent.h"		//子弹碰撞特效头文件
#include "SaturnRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API ASaturnRifleWeapon : public AAWeaponBase
{
	GENERATED_BODY()
	
public:
	ASaturnRifleWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 0.1f;					//发射间隔
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	float BulletSpread = 1.5f;						//子弹扩散角度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TraceDistance = 5000.0f;					//发射距离
	UPROPERTY(EditDefaultsOnly, Category="VFX")
	USaturnWeaponFXComponent* WeaponFXComponent;	//子弹碰撞特效

private:
	FTimerHandle ShotTimerHandle;		//发射计时器
};
