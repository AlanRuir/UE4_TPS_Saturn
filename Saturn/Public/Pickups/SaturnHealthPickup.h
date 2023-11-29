// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SaturnPickupBase.h"
#include "SaturnHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API ASaturnHealthPickup : public ASaturnPickupBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;		//拾取道具后增加的生命值
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
