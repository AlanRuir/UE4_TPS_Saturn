// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SaturnFireService.h"
#include "SaturnCharacterBase.h"
#include "AIController.h"
#include "Components/SaturnAIWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"       //黑板组件头文件
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

USaturnFireService::USaturnFireService()
{
    NodeName = "Fire";
}

void USaturnFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        //从黑板中找到敌人的Actor并对其射击
        const auto Controller = OwnerComp.GetAIOwner();
        const auto AIWeaponComponent = Cast<USaturnAIWeaponComponent>(Controller->GetPawn()->GetComponentByClass(USaturnAIWeaponComponent::StaticClass()));
        AActor* Enemy = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));       //从黑板中获取敌人的Actor

        if (Enemy && AIWeaponComponent)
        {
            FCollisionQueryParams CollisionParams;
	        CollisionParams.AddIgnoredActor(Controller);
	        FHitResult HitResult;

            if (GetWorld()->LineTraceSingleByChannel(HitResult, Controller->GetPawn()->GetActorLocation(), Enemy->GetActorLocation(), ECollisionChannel::ECC_Visibility, CollisionParams))
            {
                AIWeaponComponent->StartFire();
            }
        }

        AIWeaponComponent->StopFire();
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}