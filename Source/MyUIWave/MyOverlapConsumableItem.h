#pragma once

#include "CoreMinimal.h"
#include "MyBaseItem.h"
#include "MyOverlapConsumableItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyOverlapConsumableItem : public AMyBaseItem
{
	GENERATED_BODY()

public:
	AMyOverlapConsumableItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapConsumable")
	int32 HPAmount;		// 아이템 획득 시 HP 변화량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapConsumable")
	float SpeedAmount;	// 아이템 획득 시 이동 속도 변화량
};