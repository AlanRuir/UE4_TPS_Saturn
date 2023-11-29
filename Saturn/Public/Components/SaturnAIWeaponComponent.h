// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SaturnWeaponComponent.h"
#include "SaturnAIWeaponComponent.generated.h"

UCLASS()
class SATURN_API USaturnAIWeaponComponent : public USaturnWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
