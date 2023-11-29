// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"		//添加黑板组件头文件
#include "AIController.h"							//添加AI控制器头文件
#include "NavigationSystem.h"						//添加导航系统头文件
#include "SaturnNextLocationTask.generated.h"

UCLASS()
class SATURN_API USaturnNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USaturnNextLocationTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;		

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 1000.0f;		// 定义搜索半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocationKey;			// 定义黑板中的Key	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SelfCenter = true;		// 是否自己中心
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))		//仅当SelfCenter为false时生效
	FBlackboardKeySelector CenterKey;		// 定义黑板中的Key
};
