// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"     //增加相机组件头文件
#include "Components/InputComponent.h"  //增加输入组件头文件
#include "GameFramework/SpringArmComponent.h"   //增加弹簧臂组件头文件
#include "SaturnCharacterMovementComponent.h"	//增加移动组件头文件
#include "Components/SaturnHealthComponent.h"	//增加生命组件头文件
#include "Components/TextRenderComponent.h"     //增加生命数值显示组件头文件
#include "GameFramework/Controller.h"       //增加控制器头文件
#include "Components/SaturnWeaponComponent.h"	//增加武器组件头文件
#include "Components/CapsuleComponent.h"      //增加碰撞胶囊体组件头文件
#include "SaturnCharacterBase.generated.h"

UCLASS()
class SATURN_API ASaturnCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASaturnCharacterBase(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnDeath();                        //死亡

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;                 //判断是否开始跑步
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;     //增加相机组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;    //增加弹簧臂组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USaturnHealthComponent* HealthComponent;    //增加角色生命值组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;  //增加生命数值显示组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USaturnWeaponComponent* WeaponComponent;    //增加武器组件
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;     //死亡动画
	UPROPERTY(EditDefaultsOnly, Category="Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);    //约束着地伤害速度，若低于900则不受伤，若高于1200则直接死亡
    UPROPERTY(EditDefaultsOnly, Category="Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);              //约束着地伤害值，最小10，最大100
private:
    void MoveForward(float Value);      //前后移动
    void MoveRight(float Value);            //左右移动
	void LookUp(float Value);              //上下旋转
	void TurnAround(float Value);           //左右旋转
	void OnStartRunning();                 //开始跑步
    void OnStopRunning();                   //停止跑步
	// void OnDeath();                        //死亡
	void OnHealthChanged(float Health);        //伤害
	void ShowGameCtrlHUD();                //显示游戏控制界面
private:
	bool WantsToRun = false;                //是否开始跑步
    bool IsMovingForward = false;           //是否前进
public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;     //获取移动方向
	UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit); //着地处理函数
};
