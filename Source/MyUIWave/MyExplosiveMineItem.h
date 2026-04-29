#pragma once

#include "CoreMinimal.h"
#include "MyOverlapTrapItem.h"
#include "MyExplosiveMineItem.generated.h"

class USphereComponent;

UCLASS()
class MYUIWAVE_API AMyExplosiveMineItem : public AMyOverlapTrapItem
{
	GENERATED_BODY()

public:
	AMyExplosiveMineItem();

	USphereComponent* ActivationCollision;
	USphereComponent* ExplosionCollision;

	FTimerHandle ExplosionTimerHandle;	// 폭발 시간을 관리할 타이머 핸들러

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapTrap")
	float ExplosionRadius;
};