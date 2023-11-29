// Fill out your copyright notice in the Description page of Project Settings.


#include "SaturnCharacterBase.h"

// Sets default values
ASaturnCharacterBase::ASaturnCharacterBase(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USaturnCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));       //增加弹簧臂组件
    SpringArmComponent->SetupAttachment(GetRootComponent());        //设置弹簧臂组件的父级为根组件
    SpringArmComponent->bUsePawnControlRotation = true;     //设置弹簧臂组件的旋转模式为真实旋转
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));        //增加相机组件
    CameraComponent->SetupAttachment(SpringArmComponent);       //设置相机组件的父级为弹簧臂组件
    HealthComponent = CreateDefaultSubobject<USaturnHealthComponent>(TEXT("HealthComponent"));     //增加角色生命值组件
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));        //增加生命数值显示组件
    HealthTextComponent->SetupAttachment(GetRootComponent());       //设置生命数值显示组件的父级为根组件
    HealthTextComponent->SetOwnerNoSee(true);                       //设置生命数值显示组件不可见
    WeaponComponent = CreateDefaultSubobject<USaturnWeaponComponent>(TEXT("WeaponComponent"));        //增加武器组件
}

// Called when the game starts or when spawned
void ASaturnCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
    check(HealthComponent);         //检查角色生命值组件
    check(HealthTextComponent);     //检查生命数值显示组件
    check(GetCharacterMovement());       //检查角色移动组件
    check(WeaponComponent);       //检查武器组件
    check(GetMesh());             //检查角色网格组件

    OnHealthChanged(HealthComponent->GetHealth());      //初始化角色生命值，在这里调用这个函数的原因是HealthComponent的BeginPlay函数比AWuKongCharacterBase的BeginPlay函数先调用，则刚开始委托还没生效，角色的初始血量会是0
    HealthComponent->OnDeath.AddUObject(this, &ASaturnCharacterBase::OnDeath);     //绑定死亡委托
    HealthComponent->OnHealthChanged.AddUObject(this, &ASaturnCharacterBase::OnHealthChanged);  //绑定伤害委托

    LandedDelegate.AddDynamic(this, &ASaturnCharacterBase::OnGroundLanded);     //绑定着地委托
}

// Called every frame
void ASaturnCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    const auto Health = HealthComponent->GetHealth();       //获取角色生命值
    HealthTextComponent->SetText(FText::FromString(FString::FromInt(Health)));                  //设置生命数值
}

// Called to bind functionality to input
void ASaturnCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASaturnCharacterBase::MoveForward);    //绑定前后移动回调
    PlayerInputComponent->BindAxis("MoveRight", this, &ASaturnCharacterBase::MoveRight); 
	PlayerInputComponent->BindAxis("LookUp", this, &ASaturnCharacterBase::LookUp);              //绑定上下旋转回调
    PlayerInputComponent->BindAxis("TurnAround", this, &ASaturnCharacterBase::TurnAround);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASaturnCharacterBase::Jump);            //绑定跳跃回调
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASaturnCharacterBase::OnStartRunning);   //绑定开始跑步回调
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASaturnCharacterBase::OnStopRunning);   //绑定停止跑步回调
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USaturnWeaponComponent::StartFire);          //绑定发射武器回调
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USaturnWeaponComponent::StopFire);          //绑定停止发射武器回调
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USaturnWeaponComponent::NextWeapon);   //绑定切换武器回调
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USaturnWeaponComponent::Reload);   //绑定切换武器回调
}

void ASaturnCharacterBase::MoveForward(float Value)
{
	IsMovingForward = (Value > 0.0f);                       //判断当前是否在前进
    AddMovementInput(GetActorForwardVector(), Value);       //前后移动
}

void ASaturnCharacterBase::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);         //左右移动
}

void ASaturnCharacterBase::LookUp(float Value)
{
	AddControllerPitchInput(Value);                     //上下旋转
}

void ASaturnCharacterBase::TurnAround(float Value)
{
	AddControllerYawInput(Value);                       //左右旋转
}

void ASaturnCharacterBase::OnStartRunning()                 //开始跑步
{
    WantsToRun = true;
}

void ASaturnCharacterBase::OnStopRunning()                  //停止跑步
{
    WantsToRun = false;
}

bool ASaturnCharacterBase::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();    //判断是否开始跑步
}

float ASaturnCharacterBase::GetMovementDirection() const
{
	if (GetVelocity().IsZero())     //如果速度为0，则不计算角度
    {
        return 0.0f;
    }

    const auto VelocityNormal = GetVelocity().GetSafeNormal();  //获取当前速度的单位向量
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));    //计算点积
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);   //计算叉积
    const auto Degress = FMath::RadiansToDegrees(AngleBetween); //转换为角度

    return CrossProduct.IsZero() ? Degress : Degress * FMath::Sign(CrossProduct.Z);   
}

void ASaturnCharacterBase::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Player %s is dead!"), *GetName());
    // PlayAnimMontage(DeathAnimMontage);      //播放死亡动画

    GetCharacterMovement()->DisableMovement();      //禁止移动
    SetLifeSpan(2.0f);                              //2秒后析构角色
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);   //切换到观察状态
    }

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);     //设置碰撞通道不响应
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);     //设置碰撞模式
    GetMesh()->SetSimulatePhysics(true);                                    //开启物理模拟
}

void ASaturnCharacterBase::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::FromInt(Health)));                  //显示生命数值
}

void ASaturnCharacterBase::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;        //获取角色下落速度
    UE_LOG(LogTemp, Warning, TEXT("FallVelocityZ: %f"), FallVelocityZ);         //输出下落速度

    if (FallVelocityZ < LandedDamageVelocity.X)         //若下落速度低于最小值，则不受伤害
    {
        return;
    }

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);      //计算最终伤害，着地速度和着地伤害成正比
    UE_LOG(LogTemp, Warning, TEXT("FinalDamage: %f"), FinalDamage); //输出最终伤害
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);  //扣血
}