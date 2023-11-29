// Fill out your copyright notice in the Description page of Project Settings.


#include "SaturnGameModeBase.h"

ASaturnGameModeBase::ASaturnGameModeBase()
{
    DefaultPawnClass = ASaturnCharacterBase::StaticClass();
    PlayerControllerClass = ASaturnPlayerController::StaticClass();
    HUDClass = ASaturnGameHUD::StaticClass();
}