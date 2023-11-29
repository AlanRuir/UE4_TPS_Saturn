// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SaturnFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"       //黑板组件头文件
#include "AIController.h"                         //AI控制器头文件
#include "Components/SaturnAIPerceptionComponent.h"         //感知组件的头文件

USaturnFindEnemyService::USaturnFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USaturnFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Cast<USaturnAIPerceptionComponent>(Controller->GetPerceptionComponent());
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}