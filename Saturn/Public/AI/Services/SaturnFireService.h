// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SaturnFireService.generated.h"

UCLASS()
class SATURN_API USaturnFireService : public UBTService
{
	GENERATED_BODY()
	
public:
	USaturnFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;		//用来存储敌人的Actor的Key
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
