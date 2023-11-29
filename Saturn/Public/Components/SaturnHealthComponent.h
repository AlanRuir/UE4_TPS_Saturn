// // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"             //引入pawn头文件
#include "GameFramework/Controller.h"       //引入控制器头文件
#include "Camera/CameraShake.h"             //引入摄像机震动头文件
#include "SaturnHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);       //声明死亡委托
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);       //声明伤害委托

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SATURN_API USaturnHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public: 
    // Sets default values for this component's properties
    USaturnHealthComponent();
    float GetHealth() const;
    UFUNCTION(BlueprintCallable)
    bool IsDead() const;        //判断是否死亡

    FOnDeath OnDeath;           //声明死亡委托
    FOnHealthChanged OnHealthChanged;       //声明伤害委托
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercentage() const;
    bool IsHealthFull() const;                //判断是否满血
    bool TryToAddHealth(float Amount);        //增加生命值

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public: 
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float MaxHealth = 100.0f;       //最大生命值
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHeal = true;           //是否自动回血
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))      //仅当自动回血开启时，回血刷新率字段才使能
    float HealUpdateTime = 1.0f;    //回血刷新率（定时器参数）
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))      //仅当自动回血开启时，回血延迟字段才使能
    float HealDelay = 3.0f;         //回血延迟
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))      //仅当自动回血开启时，回血血量字段才使能
    float HealModifier = 5.0f;      //回血血量

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;      //摄像机震动
private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;       //回血定时器
private:
    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);     //伤害函数
    void HealUpdate();                  //回血函数
    void SetHealth(float NewHealth);        //设置生命值
    void PlayCameraShake();             //播放摄像机震动
};