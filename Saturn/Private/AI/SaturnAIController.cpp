// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SaturnAIController.h"
#include "AI/SaturnAICharacter.h"
#include "Components/SaturnAIPerceptionComponent.h"         //感知组件的头文件
#include "BehaviorTree/BlackboardComponent.h"       //添加黑板组件头文件

ASaturnAIController::ASaturnAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USaturnAIPerceptionComponent>(TEXT("SaturnAIPerceptionComponent"));
    SetPerceptionComponent(*AIPerceptionComponent);       //设置感知组件

    // PrimaryActorTick.bCanEverTick = true;
}

void ASaturnAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto SaturnCharacter = Cast<ASaturnAICharacter>(InPawn);
    if (SaturnCharacter)
    {
        RunBehaviorTree(SaturnCharacter->BehaviorTreeAsset);
    }
}

void ASaturnAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto AimActor = AIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);     //设置焦点
}

AActor* ASaturnAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
    {
        return nullptr;
    }

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}