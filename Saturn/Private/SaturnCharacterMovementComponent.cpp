// Fill out your copyright notice in the Description page of Project Settings.


#include "SaturnCharacterMovementComponent.h"
#include "SaturnCharacterBase.h"

float USaturnCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();        //获取最大速度
    const ASaturnCharacterBase* Player = Cast<ASaturnCharacterBase>(GetOwner());    //获取当前角色
    return (Player && Player->IsRunning()) ? MaxSpeed * RunModifier : MaxSpeed; 
}
