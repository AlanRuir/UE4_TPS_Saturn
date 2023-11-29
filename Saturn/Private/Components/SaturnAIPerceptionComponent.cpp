// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SaturnAIPerceptionComponent.h"
#include "AIController.h"       //AI控制器头文件
#include "Components/SaturnHealthComponent.h"       //血量组件头文件
#include "Perception/AISense_Sight.h"                //视觉感知头文件
#include "AI/SaturnAIController.h"                //AI控制器头文件

AActor* USaturnAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceivedActors;        //感知到的敌人
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);        //获取感知到的敌人
    if (0 == (PerceivedActors.Num()))
    {
        return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
    {
        return nullptr;
    }

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
    {
        return nullptr;
    }

    float BestDistance = MAX_FLT;       //最佳距离
    AActor* BestPawn = nullptr;         //最佳敌人
    for (const auto PerceivedActor : PerceivedActors)
    {
        const auto HealthComponent = PerceivedActor->FindComponentByClass<USaturnHealthComponent>();
        if (HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PerceivedActor;
            }
        }
    }

    return BestPawn;
}