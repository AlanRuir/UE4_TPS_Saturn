// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/SaturnNextLocationTask.h"

USaturnNextLocationTask::USaturnNextLocationTask()
{
    NodeName = "Next Location";     // 节点名称
}

EBTNodeResult::Type USaturnNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();     // 获取AI控制器
    const auto Blackboard = OwnerComp.GetBlackboardComponent();     // 获取黑板组件
    if (!Controller || !Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);      // 获取导航系统
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation NavLocation;       
    auto Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterKey.SelectedKeyName));     // 获取中心点
        if (!CenterActor)
        {
            return EBTNodeResult::Failed;
        }
        Location = CenterActor->GetActorLocation();
    }
    const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);     // 在半径范围内随机获取一个点
    if (!Found)
    {
        return EBTNodeResult::Failed;
    }

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);     // 将随机获取的点设置到黑板中
    return EBTNodeResult::Succeeded;
}