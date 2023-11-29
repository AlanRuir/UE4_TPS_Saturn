// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SaturnHealthPickup.h"
#include "Components/SaturnHealthComponent.h"

bool ASaturnHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = Cast<USaturnHealthComponent>(PlayerPawn->GetComponentByClass(USaturnHealthComponent::StaticClass()));
    if (!HealthComponent)
    {
        return false;
    }

    return HealthComponent->TryToAddHealth(HealthAmount);
}

