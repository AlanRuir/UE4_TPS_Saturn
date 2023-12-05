// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaturnGameHUD.h"
#include "Engine/Canvas.h"      //添加绘制2D图形的头文件
#include "Blueprint/UserWidget.h"       //添加用户界面的头文件
#include "UI/SaturnPlayerHUDWidget.h"       //添加用户界面的头文件

void ASaturnGameHUD::DrawHUD()
{
    Super::DrawHUD();

    // DrawCrossHair();
}

void ASaturnGameHUD::BeginPlay()
{
    Super::BeginPlay();

    PlayerHUDWidgetClass = GetClass()->GetDefaultObject<ASaturnGameHUD>()->PlayerHUDWidgetClass;
    GameCtrlHUDWidgetClass = GetClass()->GetDefaultObject<ASaturnGameHUD>()->GameCtrlHUDWidgetClass;

    if (!PlayerHUDWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerHUDWidgetClass is nullptr"));
        return;
    }

    if (!GameCtrlHUDWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameCtrlHUDWidgetClass is nullptr"));
        return;
    }

    GameCtrlHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameCtrlHUDWidgetClass);
    PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (GameCtrlHUDWidget && PlayerHUDWidget)
    {
        GameCtrlHUDWidget->AddToViewport();     //添加到屏幕
        GameCtrlHUDWidget->SetVisibility(ESlateVisibility::Visible);        //显示界面
        PlayerHUDWidget->AddToViewport();       //添加到屏幕
        PlayerHUDWidget->SetVisibility(ESlateVisibility::Hidden);        //隐藏界面

        // 设置输入模式为UI模式，并显示鼠标
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            FInputModeUIOnly InputMode;     //UI模式
            InputMode.SetWidgetToFocus(GameCtrlHUDWidget->TakeWidget());        //设置焦点
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);        //不锁定鼠标

            PlayerController->SetInputMode(InputMode);      //设置输入模式
            PlayerController->bShowMouseCursor = true;      //显示鼠标
        }
    }
}

void ASaturnGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);      //TInterval是一个表示范围的类型
    const float HalfLineSize = 10.0f;                                                    //线的大小
    const float LineThickness = 2.0f;                                                   //线的粗细
    const FLinearColor LineColor = FLinearColor::Green;                                 //线的颜色
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness); //绘制十字线
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASaturnGameHUD::ShowGameCtrlHUD()
{
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameCtrlHUDWidget)
    {
        GameCtrlHUDWidget->SetVisibility(ESlateVisibility::Visible);

        // 设置输入模式为UI模式，并显示鼠标
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            FInputModeUIOnly InputMode;     //UI模式
            InputMode.SetWidgetToFocus(GameCtrlHUDWidget->TakeWidget());        //设置焦点
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);        //不锁定鼠标

            PlayerController->SetInputMode(InputMode);      //设置输入模式
            PlayerController->bShowMouseCursor = true;      //显示鼠标
        }
    }
}

void ASaturnGameHUD::ShowPlayerHUD()
{
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
    }
    if (GameCtrlHUDWidget)
    {
        GameCtrlHUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ASaturnGameHUD::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));
}