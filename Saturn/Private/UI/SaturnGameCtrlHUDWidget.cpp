// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaturnGameCtrlHUDWidget.h"
#include "UI/SaturnGameHUD.h"

void USaturnGameCtrlHUDWidget::StartGame()
{
    ASaturnGameHUD* HUD = Cast<ASaturnGameHUD>(GetOwningPlayer()->GetHUD());
    if (HUD)
    {
        // 隐藏GameCtrlHUDWidget，显示PlayerHUDWidget，开始游戏
        HUD->ShowPlayerHUD();
        HUD->StartGame();
    }

    // 获取玩家控制器
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // 设置输入模式为游戏模式
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);

        // 隐藏鼠标光标
        PlayerController->bShowMouseCursor = false;
    }
}

void USaturnGameCtrlHUDWidget::EndGame()
{
    GetOwningPlayer()->ConsoleCommand("Quit");      //退出游戏
}