// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SaturnAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API USaturnAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosestEnemy() const;		//获取最近的敌人
};
