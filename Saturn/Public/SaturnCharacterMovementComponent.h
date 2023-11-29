// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SaturnCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API USaturnCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
    virtual float GetMaxSpeed() const override;     //获取最大速度重载
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunModifier = 2.0f;
};
