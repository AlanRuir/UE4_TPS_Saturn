// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SaturnAICharacter.h"
#include "AI/SaturnAIController.h"
#include "GameFramework/CharacterMovementComponent.h"       //移动组件头文件
#include "Components/SaturnAIWeaponComponent.h"             //AI武器组件头文件

ASaturnAICharacter::ASaturnAICharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USaturnAIWeaponComponent>(TEXT("WeaponComponent")))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASaturnAIController::StaticClass();

    bUseControllerRotationYaw = false;          //不使用控制器的旋转
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;               //面向移动方向
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);    //旋转速率
    }
}