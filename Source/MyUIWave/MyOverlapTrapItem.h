#pragma once

#include "CoreMinimal.h"
#include "MyBaseItem.h"
#include "MyOverlapTrapItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyOverlapTrapItem : public AMyBaseItem
{
	GENERATED_BODY()

public:
	AMyOverlapTrapItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapTrap")
	int32 DamageAmount;		// 트랩 데미지량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapTrap")
	float SpeedAmount;	// 트랩 피격시 이동 속도 변화량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapTrap")
	float DelayTime;	// 트랩 타이머 시작 후 발동까지 걸리는 시간
};