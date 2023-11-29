// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/AWeaponBase.h"			//增加武器组件头文件
#include "GameFramework/Character.h"		//增加角色组件头文件
#include "Animations/SaturnAnimNotify.h"		//增加动画通知头文件
#include "Animations/SaturnEquipFinishedAnimNotify.h"		//增加切枪动画通知头文件
#include "Animations/SaturnReloadFinishedAnimNotify.h"		//增加换弹动画通知头文件
#include "Animation/AnimMontage.h"				//增加切枪动画头文件
#include "SaturnWeaponComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AAWeaponBase> WeaponClass;					//AAWeaponBase类

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UAnimMontage* ReloadAnim;				//武器换弹动画
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SATURN_API USaturnWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USaturnWeaponComponent();
	// void StartFire();
	virtual void StartFire();
	void StopFire();
	// void NextWeapon();			//切换武器回调函数
	virtual void NextWeapon();			//切换武器回调函数
	void Reload();				//换弹回调函数
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;		//获取武器UI信息
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;		//获取子弹信息
	bool TryToAddAmmo(TSubclassOf<AAWeaponBase> WeaponType, int32 ClipsAmount);			//尝试添加子弹

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
protected:
	// UPROPERTY(EditDefaultsOnly, Category="Weapon")
    // TArray<TSubclassOf<AAWeaponBase>> WeaponClasses;                    //AAWeaponBase类
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponData;						//武器数据
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";		//武器插槽名称
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";		//背包插槽名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UAnimMontage* EquipMontage = nullptr;				//切枪动画
	UPROPERTY()
	AAWeaponBase* CurrentWeapon = nullptr;				//当前武器
	UPROPERTY()
	TArray<AAWeaponBase*> Weapons;						//武器库
	bool CanEquip() const;									//判断是否可以切枪
	bool CanFire() const;									//判断是否可以发射
	void EquipWeapon(int32 WeaponIndex);		//选择武器
	int32 CurrentWeaponIndex = 0;						//当前武器索引
private:
	// void SpawnWeapon();						//生成武器并附加在插槽上
	void SpawnWeapons();					//生成所有武器
	void AttachWeaponToSocket(AAWeaponBase* Weapon, USceneComponent* SceneComponent, const FName& SocketName);		//安装武器到对应插槽上
	// void EquipWeapon(int32 WeaponIndex);		//选择武器
	void PlayAnimMontage(UAnimMontage* AnimMontage);		//播放切枪动画
	void InitAnimation();					//初始化切枪动画
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);				//切枪完成
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);				//换弹完成
	// bool CanEquip() const;									//判断是否可以切枪
	// bool CanFire() const;									//判断是否可以发射
	bool CanReload() const;									//判断是否可以换弹
private:
	// UPROPERTY()
	// AAWeaponBase* CurrentWeapon = nullptr;				//当前武器
	// UPROPERTY()
	// TArray<AAWeaponBase*> Weapons;						//武器库
	// int32 CurrentWeaponIndex = 0;						//当前武器索引
	bool EquipAnimationInProgress = false;				//切枪动画是否进行中
	bool ReloadAnimationInProgress = false;				//换弹动画是否进行中
	UPROPERTY()
	UAnimMontage* CurrentReloadAnim = nullptr;			//当前武器换弹动画

	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation)
		{
			return nullptr;
		}

		const auto NotifyEvents = Animation->Notifies;		//蒙太奇动画的通知
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			if (AnimNotify)
			{
				return AnimNotify;
			}
		}

		return nullptr;
	}
};
