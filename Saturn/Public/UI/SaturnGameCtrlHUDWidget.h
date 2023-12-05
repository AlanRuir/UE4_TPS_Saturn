// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaturnGameCtrlHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SATURN_API USaturnGameCtrlHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void StartGame();	//开始游戏
	UFUNCTION(BlueprintCallable, Category = "UI")
	void EndGame();		//结束游戏
};
