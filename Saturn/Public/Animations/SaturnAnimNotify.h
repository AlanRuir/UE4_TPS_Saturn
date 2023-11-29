// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SaturnAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipFinished, USkeletalMeshComponent*);		//声明切枪完成委托

/**
 * 
 */
UCLASS()
class SATURN_API USaturnAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;		//当动画通知被触发时会自动调用

	FOnEquipFinished OnNotified;		//切枪完成委托
};
