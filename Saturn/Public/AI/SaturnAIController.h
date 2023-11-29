// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SaturnAIController.generated.h"

class USaturnAIPerceptionComponent;		//感知组件类的前向声明

UCLASS()
class SATURN_API ASaturnAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASaturnAIController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;		//控制角色
	virtual void Tick(float DeltaTime) override;			//控制角色
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USaturnAIPerceptionComponent* AIPerceptionComponent;		//感知组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";		//焦点

private:
	AActor* GetFocusOnActor() const;
};
