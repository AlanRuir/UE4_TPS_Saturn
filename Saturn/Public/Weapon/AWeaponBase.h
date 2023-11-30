// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "AWeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets = 0;		//子弹数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Clips = 0;		//弹夹数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool Infinite = false;		//是否无限弹夹
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UTexture2D* MainIcon;		//武器图标
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UTexture2D* CrossHairIcon;		//准心图标
};

UCLASS()
class SATURN_API AAWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAWeaponBase();

	virtual void StartFire();							//发射
	virtual void StopFire();							//停止发射
	FWeaponUIData GetUIData() const;					//获取武器UI信息
	FAmmoData GetAmmoData() const;					//获取子弹信息
	bool TryToAddAmmo(int32 ClipsAmount);				//尝试添加子弹
	bool IsAmmoEmpty() const;		//弹匣是否为空
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;				//武器组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	FName MuzzleSocketName = "MuzzleSocket";		//枪口
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	float TraceMaxDistance = 1500.0f;				//发射距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 3.0f;						//伤害值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	FAmmoData DefaultAmmo{15, 5, false};			//弹匣信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;							//武器UI信息
protected:
	virtual void MakeShot();		//使其变为一个虚函数
	void MakeDamage(const FHitResult& HitResult);
	void DecreaseAmmo();			//减少子弹
	// bool IsAmmoEmpty() const;		//弹匣是否为空
	bool IsClipEmpty()const;		//弹夹是否为空
	void ChangeClip();				//切换弹夹
	void LogAmmo();					//打印弹匣信息
	bool IsAmmoFull() const;		//弹匣是否满
private:
	FAmmoData CurrentAmmo;			//当前弹匣
};
