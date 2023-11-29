// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SaturnWeaponFXComponent.h"

USaturnWeaponFXComponent::USaturnWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USaturnWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	// auto Effect = DefaultEffect;
	auto ImpactData = DefaultImpactData;
	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();		//获取物理材质
		// if (EffectsMap.Contains(PhysMat))					//判断材质是否在材质-子弹碰撞特效映射中
		// {
		// 	Effect = EffectsMap[PhysMat];
		// }
		if (ImpactDataMap.Contains(PhysMat))					//判断材质是否在材质-子弹碰撞特效映射中
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}
	// if (!Effect)
	// {
	// 	return;
	// }
	// UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());		//播放子弹碰撞特效
	// 生成子弹碰撞特效
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());		//播放子弹碰撞特效
	// 生成贴花
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}
