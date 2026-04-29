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

private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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