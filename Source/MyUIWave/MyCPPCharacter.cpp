#include "MyCPPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCPPCharacter::AMyCPPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f; // SpringArm 기본 거리 
	SpringArmComp->bUsePawnControlRotation = true;
	// Pawn을 컨트롤 할 때 SpringArm도 같이 이동

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// USpringArmComponent::SocketName 이라고 정의되어 있는 끝부분에 부착
	CameraComp->bUsePawnControlRotation = false;
	// 카메라 자체는 움직이지 않고 SpringArm에 고정되어 있도록 비활성화

	OriginSpeed = 600.0f;		// const라서 Initializer list로 초기화 예정
	NormalSpeed = OriginSpeed;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	// 현재 Character의 MaxWalkSpeed 를 NormalSpeed로 설정

	// 체력 초기화
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void AMyCPPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)	// nullptr 인지 확인 후
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,	// 만들었던 IA MoveAction 에
					ETriggerEvent::Triggered,	// Key가 눌려서 Event가 발생했을때
					this,	// 현재 Character 객체의
					&AMyCPPCharacter::Move	// Move 함수를 IA MoveAction 에 바인딩
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCPPCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AMyCPPCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCPPCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCPPCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AMyCPPCharacter::StopSprint
				);
			}
		}
	}
}

float AMyCPPCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void AMyCPPCharacter::AddCurrentHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health increased to : %f"), CurrentHealth);
}

float AMyCPPCharacter::TakeDamage(
	float DamageAmount, 
	FDamageEvent const& DamageEvent, 
	AController* EventInstigator, 
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// ActualDamage = 방어력, 감소, 증폭 등 모든 요소를 고려하여 실제로 입을 데미지

						// CurrentHealth - DamageAmount의 결과가 최소 0.0, 최대 MaxHealth가 되도록 보정
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Take Damage, Health decreased to : %f"), CurrentHealth);
	
	if (CurrentHealth <= 0.0f)
	{
		OnDeath();
	}

	return ActualDamage;
}

float AMyCPPCharacter::GetNormalSpeed() const
{
	return NormalSpeed;
}

void AMyCPPCharacter::AddNormalSpeed(float Amount, float Duration)
{
	// 새로운 속도 효과를 리스트에 추가
	FSpeedEffect NewEffect;
	NewEffect.Amount = Amount;
	NewEffect.Duration = Duration;
	ActiveSpeedEffects.Add(NewEffect);

	// 총 속도를 계산해서 적용
	UpdateSpeed();

	// 해당 효과의 타이머를 등록하여 지속시간 동안 유지
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, Amount]()
		{
			// 타이머가 끝날 때, 해당 속도 효과 제거
			RemoveSpeedEffect(Amount);
			UpdateSpeed();  // 속도를 다시 업데이트

			// 활성화된 효과가 더 이상 없으면, NormalSpeed를 OriginSpeed로 복원
			if (ActiveSpeedEffects.Num() == 0)
			{
				SetNormalSpeed(OriginSpeed);  // 최종 속도를 원래 값으로 복원
				GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;  // MaxWalkSpeed도 복원
			}
		});

	// Timer 등록 - 각 타이머 핸들을 `SpeedTimerHandles` 배열에 저장
	FTimerHandle NewTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		NewTimerHandle,           // 새로 생성된 타이머 핸들
		TimerDelegate,            // 실행할 함수 (람다 함수)
		Duration,                 // 타이머 지속 시간
		false                     // 한 번만 실행
	);

	// 타이머 핸들을 배열에 추가
	SpeedTimerHandles.Add(NewTimerHandle);
}

void AMyCPPCharacter::UpdateSpeed()
{
	float TotalSpeedIncrease = 0.0f;

	// 모든 활성화된 효과를 합산
	for (const FSpeedEffect& Effect : ActiveSpeedEffects)
	{
		TotalSpeedIncrease += Effect.Amount;
	}

	// NormalSpeed에 합산된 속도 증가분 적용
	SetNormalSpeed(OriginSpeed + TotalSpeedIncrease);

	// 실제 이동 속도에도 적용
	GetCharacterMovement()->MaxWalkSpeed = GetNormalSpeed();
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
}

void AMyCPPCharacter::RemoveSpeedEffect(float Amount)
{
	// 효과 리스트에서 해당 Amount를 가진 효과를 제거
	for (int32 i = 0; i < ActiveSpeedEffects.Num(); ++i)
	{
		if (ActiveSpeedEffects[i].Amount == Amount)
		{
			ActiveSpeedEffects.RemoveAt(i);
			break;  // 첫 번째로 일치하는 효과만 제거
		}
	}
}

void AMyCPPCharacter::SetNormalSpeed(float InSpeed)
{
	NormalSpeed = InSpeed;
}

void AMyCPPCharacter::OnDeath()
{
	// 사망 처리 ex) 게임 종료
}

void AMyCPPCharacter::Move(const FInputActionValue& value)	// Axis2D = 2D Vector
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	FRotator ControlRot = Controller->GetControlRotation();

	FRotator YawRot(0.f, ControlRot.Yaw, 0.f); // Pitch는 제거하고 Yaw만 사용

	FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	// 부동 소수점 관련해서는 IsNearlyZero를 붙이는게 좋음
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(Forward, MoveInput.X);
		// Character 클래스는 이런 AddMovementInput 같은 함수들이 제공됨
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(Right, MoveInput.Y);
	}
}

void AMyCPPCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{	// 함수 내부에 이미 Controller 체크 코드가 있음
		Jump();	// Character 클래스에서 이미 구현되어 있는 기능
	}
}

void AMyCPPCharacter::StopJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{	// 함수 내부에 이미 Controller 체크 코드가 있음
		StopJumping();	// Character 클래스에서 이미 구현되어 있는 기능
	}
}

void AMyCPPCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X); // Character 클래스에서 이미 구현되어 있는 기능
	// Yaw는 좌우 회전

	AddControllerPitchInput(LookInput.Y); // Character 클래스에서 이미 구현되어 있는 기능
	// Pitch는 상하 회전
}

void AMyCPPCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AMyCPPCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}