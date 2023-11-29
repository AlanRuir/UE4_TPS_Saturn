// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/SaturnAnimNotify.h"

void USaturnAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);            //切枪完成
    Super::Notify(MeshComp, Animation);     //当动画通知被触发时会自动调用
}