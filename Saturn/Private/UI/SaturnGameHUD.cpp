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

    if (!PlayerHUDWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerHUDWidgetClass is nullptr"));
        return;
    }

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
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