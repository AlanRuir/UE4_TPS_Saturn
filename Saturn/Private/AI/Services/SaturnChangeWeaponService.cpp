// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SaturnChangeWeaponService.h"
#include "AIController.h"
#include "Components/SaturnWeaponComponent.h"

USaturnChangeWeaponService::USaturnChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USaturnChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USaturnWeaponComponent>();
    if (WeaponComponent && Probability > 0.0f && FMath::FRand() <= Probability)
    {
        WeaponComponent->NextWeapon();
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

