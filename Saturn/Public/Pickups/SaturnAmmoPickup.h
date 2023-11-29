// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SaturnPickupBase.h"
#include "Weapon/AWeaponBase.h"		//武器基类头文件
#include "Components/SaturnHealthComponent.h"		//生命值组件头文件
#include "Components/SaturnWeaponComponent.h"		//武器组件头文件
#include "SaturnAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API ASaturnAmmoPickup : public ASaturnPickupBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;							//弹夹数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<AAWeaponBase> WeaponType;				//武器类型
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
