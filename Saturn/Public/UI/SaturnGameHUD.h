// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"       //添加用户界面的头文件
#include "SaturnGameHUD.generated.h"

UCLASS()
class SATURN_API ASaturnGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;		//DrawHUD是一个虚函数，它每帧都会被调用，用于绘制HUD
private:
	void DrawCrossHair();					//绘制十字线(准心)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass = nullptr;

	virtual void BeginPlay() override;
};
