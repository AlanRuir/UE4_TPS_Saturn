// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SaturnChangeWeaponService.generated.h"

UCLASS()
class SATURN_API USaturnChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
	USaturnChangeWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5f;		//切枪概率

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
