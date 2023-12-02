// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaturnCharacterBase.h"
#include "SaturnAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SATURN_API ASaturnAICharacter : public ASaturnCharacterBase
{
	GENERATED_BODY()
	
public:
	ASaturnAICharacter(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;		//行为树

protected:
	virtual void OnDeath() override;                        //死亡
};
