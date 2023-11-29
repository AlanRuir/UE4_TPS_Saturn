// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SaturnFindEnemyService.generated.h"

UCLASS()
class SATURN_API USaturnFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
	USaturnFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;		//用来存储敌人的Actor的Key
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;		//重写TickNode
};
