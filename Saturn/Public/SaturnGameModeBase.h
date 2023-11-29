// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaturnCharacterBase.h"
#include "SaturnPlayerController.h"
#include "UI/SaturnGameHUD.h"
#include "SaturnGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API ASaturnGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASaturnGameModeBase();
};
