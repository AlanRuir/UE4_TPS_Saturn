// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SaturnWeaponComponent.h"

constexpr static int32 WeaponNum = 2;

USaturnWeaponComponent::USaturnWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USaturnWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// SpawnWeapon();      //生成武器
	CurrentWeaponIndex = 0;
	InitAnimation();		//初始化切枪动画
	SpawnWeapons();			//生成所有武器	
	EquipWeapon(CurrentWeaponIndex);
}

void USaturnWeaponComponent::SpawnWeapons()
{
    if (!GetWorld())
    {
        return;
    }

	ACharacter* Character = Cast<ACharacter>(GetOwner());		//获取拥有者
	if (!Character)
	{
		return;
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<AAWeaponBase>(OneWeaponData.WeaponClass);		//生成武器
    	if (!Weapon)
    	{
        	continue;
    	}

		Weapon->SetOwner(Character);		//设置武器的拥有者，即为玩家
		Weapons.Add(Weapon);				//将生成的武器加入到武器库

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);		//安装武器到背包
	}
}

void USaturnWeaponComponent::AttachWeaponToSocket(AAWeaponBase* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);        //应用插槽的旋转规则
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);      //第三个参数就是我们刚才创建的插槽名称
}

void USaturnWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());		//获取拥有者
	if (!Character)
	{
		return;
	}

	if (CurrentWeapon)
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[CurrentWeaponIndex];						//获取当前武器
	// CurrentReloadAnim = WeaponData[CurrentWeaponIndex].ReloadAnim;		//获取当前武器换弹动画
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) 	//查找武器数据
	{ return Data.WeaponClass == CurrentWeapon->GetClass(); });								//获取当前武器数据
	CurrentReloadAnim = CurrentWeaponData ? CurrentWeaponData->ReloadAnim : nullptr;		//获取当前武器换弹动画
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimationInProgress = true;		//设置切枪动画进行中
	PlayAnimMontage(EquipMontage);		//播放切枪动画
}

void USaturnWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}

	CurrentWeapon->StartFire();		//发射
}

void USaturnWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StopFire();		//停止发射
}

void USaturnWeaponComponent::NextWeapon()
{
	if (!CanEquip())		//判断是否可以切枪
	{
		return;
	}

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USaturnWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());		//获取拥有者
	if (!Character)
	{
		return;
	}

	Character->PlayAnimMontage(AnimMontage);		//播放切枪动画
}

void USaturnWeaponComponent::InitAnimation()
{
	auto EquipFinishedNotify = FindNotifyByClass<USaturnEquipFinishedAnimNotify>(EquipMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USaturnWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find %s's equip notify"), *EquipMontage->GetName());
		checkNoEntry();			//检查是否没有找到
	}

	for (auto OneWeapon : WeaponData)
	{
		auto ReloadFinishedNotify = FindNotifyByClass<USaturnReloadFinishedAnimNotify>(OneWeapon.ReloadAnim);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find %s's reload notify"), *EquipMontage->GetName());
			checkNoEntry();			//检查是否没有找到
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &USaturnWeaponComponent::OnReloadFinished);
	}
}

void USaturnWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());		//获取拥有者
	if (!Character || Character->GetMesh() != MeshComp)
	{
		return;
	}

	EquipAnimationInProgress = false;				//设置切枪动画未进行中
}

void USaturnWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());		//获取拥有者
	if (!Character || Character->GetMesh() != MeshComp)
	{
		return;
	}

	ReloadAnimationInProgress = false;				//设置换弹动画未进行中
}

bool USaturnWeaponComponent::CanEquip() const
{
	return !EquipAnimationInProgress && !ReloadAnimationInProgress;		//判断是否可以切枪
}

bool USaturnWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimationInProgress && !ReloadAnimationInProgress;		//判断是否可以发射
}

bool USaturnWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimationInProgress && !ReloadAnimationInProgress;		//判断是否可以换弹
}

void USaturnWeaponComponent::Reload()
{
	if (!CanReload())
	{
		return;
	}

	ReloadAnimationInProgress = true;		//设置换弹动画进行中
	PlayAnimMontage(CurrentReloadAnim);		//播放换弹动画
}

bool USaturnWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}

	return false;
}

bool USaturnWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}

	return false;
}

bool USaturnWeaponComponent::TryToAddAmmo(TSubclassOf<AAWeaponBase> WeaponType, int32 ClipsAmount)
{
	for (const auto OneWeapon : Weapons)
	{
		if (OneWeapon && OneWeapon->IsA(WeaponType))
		{
			return OneWeapon->TryToAddAmmo(ClipsAmount);
		}
	}

	return false;
}