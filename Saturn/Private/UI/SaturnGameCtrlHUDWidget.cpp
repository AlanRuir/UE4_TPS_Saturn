// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaturnGameCtrlHUDWidget.h"
#include "UI/SaturnGameHUD.h"
#include "Kismet/GameplayStatics.h"

void USaturnGameCtrlHUDWidget::StartGame()
{
    ASaturnGameHUD* HUD = Cast<ASaturnGameHUD>(GetOwningPlayer()->GetHUD());
    if (HUD)
    {
        HUD->StartGame();
    }

    // 加载level
    UGameplayStatics::OpenLevel(this, FName(*HUD->GetPlayerLevelName()));
}

void USaturnGameCtrlHUDWidget::EndGame()
{
    GetOwningPlayer()->ConsoleCommand("Quit");      //退出游戏
}