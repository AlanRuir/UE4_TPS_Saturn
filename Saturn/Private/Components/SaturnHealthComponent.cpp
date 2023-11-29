// // Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SaturnHealthComponent.h"
#include "GameFramework/Actor.h"        //添加Actor头文件
#include "Engine/World.h"               //添加World头文件
#include "TimerManager.h"               //添加TimerManager头文件

// Sets default values for this component's properties
USaturnHealthComponent::USaturnHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;      //将其修改为false，并直接删除TickComponent函数
}

void USaturnHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0.0f);                //检查最大生命值是否大于0
    SetHealth(MaxHealth);                   //设置生命值

    AActor* Owner = GetOwner();     //获取角色
    if (Owner)
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &USaturnHealthComponent::OnTakeAnyDamageHandle);    //添加伤害回调,OnTakeAnyDamage是默认的伤害委托
    }
}

float USaturnHealthComponent::GetHealth() const
{
    return Health;
}

void USaturnHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (FMath::IsNearlyZero(Damage) || IsDead() ||  !GetWorld())
    {
        return;
    }

    SetHealth(Health - Damage);     //设置生命值 

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);      //当角色受到伤害时停止回血

    if (IsDead())                                                       //判断角色是否死亡,如果死亡就触发死亡委托
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal && Health < MaxHealth)        //判断角色是否需要回血
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USaturnHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);       //设置回血定时器
    }

    PlayCameraShake();      //播放摄像机震动
}

bool USaturnHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

void USaturnHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);       //设置生命值

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())      //判断角色是否需要回血
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);      //清除回血定时器
    }
}

void USaturnHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);      //生命值变化，调用伤害委托
}

float USaturnHealthComponent::GetHealthPercentage() const
{
    return Health / MaxHealth;
}

bool USaturnHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USaturnHealthComponent::TryToAddHealth(float Amount)
{
    if (IsDead() || IsHealthFull())
    {
        return false;
    }

    SetHealth(Health + Amount);
    return true;
}

void USaturnHealthComponent::PlayCameraShake()
{
    if (IsDead())
    {
        return;
    }

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
    {
        return;
    }

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller)
    {
        return;
    }

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);         //播放摄像机震动
}