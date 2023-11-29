// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"				//Niagara头文件
#include "PhysicalMaterials/PhysicalMaterial.h"		//物理材质头文件
#include "Components/DecalComponent.h"			//碰撞头文件
#include "Kismet/GameplayStatics.h"				//GameplayStatics头文件
#include "SaturnWeaponFXComponent.generated.h"

USTRUCT(BlueprintType)
struct FDecalData		//子弹碰撞特效数据
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;		//材质
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);		//尺寸
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;			//生命周期
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;		//淡出时间
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;		//Niagara特效
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;				//子弹碰撞特效
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SATURN_API USaturnWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USaturnWeaponFXComponent();
	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	// UNiagaraSystem* Effect;		//子弹碰撞特效
	// UNiagaraSystem* DefaultEffect;		//默认子弹碰撞特效	
	FImpactData DefaultImpactData;			//默认子弹碰撞特效
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	// TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;		//材质-子弹碰撞特效映射
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;		//材质-子弹碰撞特效映射
};
