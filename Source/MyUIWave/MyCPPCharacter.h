#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCPPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class MYUIWAVE_API AMyCPPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCPPCharacter();

	// VisibleAnywhere : 세부 속성은 조절 불가능하지만 내부적으로 기본으로 존재하는 속성들은 수정 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

private:
	float NormalSpeed;
	float OriginSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;

	struct FSpeedEffect
	{
		float Amount;      // 속도 증가량
		float Duration;    // 효과 지속 시간
	};

	TArray<FSpeedEffect> ActiveSpeedEffects; // 활성화된 속도 효과 리스트

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const;
	// 현재 체력 Getter, BlueprintPure : Getter에 사용

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddCurrentHealth(float Amount);	// 현재 체력 증가

	// Static 함수 : 객체 생성 없이도 바로 호출할 수 있는 함수
	// 어떤 Actor에 데미지를 입혔는지 알 수 있음 -> 해당 Actor에 AActor::TakeDamage() 호출
	// AActor::TakeDamage() 는 오버라이딩이 가능하기 때문에 방어력, 데미지 감소 등의 요소를 커스텀이 가능함
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,		// 데미지 유형 ex) World, 불, 물, ...
		AController* EventInstigator,		// 데미지를 입히는 주체 ex) World, 상대 몬스터, 
		AActor* DamageCauser) override;		// 데미지를 실제로 입힌 오브젝트 ex) 총알

	TArray<FTimerHandle> SpeedTimerHandles;  // 각 속도 효과에 대한 타이머 핸들을 관리하는 배열

	UFUNCTION(BlueprintPure, Category = "Speed")
	float GetNormalSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Speed")
	void AddNormalSpeed(float Amount, float duration);	// 지속시간 동안 기본 이동속도 증가

	void SetNormalSpeed(float InSpeed);
	
	void OnDeath();

	UFUNCTION()
	void UpdateSpeed();

	UFUNCTION()
	void RemoveSpeedEffect(float Amount);

	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void StartJump(const FInputActionValue& value);

	UFUNCTION()
	void StopJump(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
};