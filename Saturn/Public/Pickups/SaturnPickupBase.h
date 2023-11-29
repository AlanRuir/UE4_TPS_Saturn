// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"		//碰撞组件头文件
#include "SaturnPickupBase.generated.h"

UCLASS()
class SATURN_API ASaturnPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASaturnPickupBase();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;		//碰撞组件
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;			//开始重叠，当Actor的子类对象碰撞组件重叠时自动调用
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float RespawnTime = 5.0f;		//重生时间

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void PickupWasTaken();				//拾取
	void Respawn();						//重生
	virtual bool GivePickupTo(APawn* PlayerPawn);		//拾取道具响应函数
	float RotationYaw = 0.0f;			//旋转角度
	void GenerateRotationYaw();			//生成旋转角度
};
