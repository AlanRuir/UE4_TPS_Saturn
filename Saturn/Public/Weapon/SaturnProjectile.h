// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"		//碰撞组件头文件
#include "GameFramework/ProjectileMovementComponent.h"		//子弹移动组件头文件
#include "DrawDebugHelpers.h"		//绘制辅助头文件
#include "Kismet/GameplayStatics.h"			//静态函数头文件
#include "Weapon/SaturnWeaponFXComponent.h"		//子弹碰撞特效头文件
#include "SaturnProjectile.generated.h"

UCLASS()
class SATURN_API ASaturnProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASaturnProjectile();
	void SetShotDirection(const FVector& Direction);		//设置子弹方向

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Weapon")
	USphereComponent* CollisionComponent;		//碰撞组件
	UPROPERTY(EditAnywhere, Category="Weapon")
	UProjectileMovementComponent* ProjectileMovementComponent;		//子弹移动组件
	UPROPERTY(EditAnywhere, Category="Weapon")
	float DamageRadius = 200.0f;		//伤害半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 50.0f;		//伤害值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	bool DoFullDamage = false;		//是否全伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float LifeSeconds = 5.0f;		//生命期
	UPROPERTY(EditDefaultsOnly, Category="VFX")
	USaturnWeaponFXComponent* WeaponFXComponent;	//子弹碰撞特效

private:
	FVector ShotDirection;
private:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	AController* GetController() const;		//获取控制器
};
