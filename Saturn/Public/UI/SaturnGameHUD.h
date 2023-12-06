// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"       //添加用户界面的头文件
#include "UI/SaturnPlayerHUDWidget.h"       //添加用户界面的头文件
#include "UI/SaturnGameCtrlHUDWidget.h"       //添加用户界面的头文件
#include "SaturnGameHUD.generated.h"

UCLASS()
class SATURN_API ASaturnGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;		//DrawHUD是一个虚函数，它每帧都会被调用，用于绘制HUD
	void ShowGameCtrlHUD();				//显示游戏控制界面
	void ShowPlayerHUD();				//显示玩家HUD
	void StartGame();					//开始游戏
	FString GetGameCtrlLevelName() const;
	FString GetPlayerLevelName() const;
private:
	void DrawCrossHair();					//绘制十字线(准心)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameCtrlHUDWidgetClass = nullptr;
	UPROPERTY()
    UUserWidget* GameCtrlHUDWidget;		//游戏控制界面
    UPROPERTY()
    UUserWidget* PlayerHUDWidget;		//玩家HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString GameCtrlLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString PlayerLevelName;

	virtual void BeginPlay() override;
};
