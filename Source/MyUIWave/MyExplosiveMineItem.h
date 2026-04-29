#pragma once

#include "CoreMinimal.h"
#include "MyOverlapTrapItem.h"
#include "MyExplosiveMineItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyExplosiveMineItem : public AMyOverlapTrapItem
{
	GENERATED_BODY()

public:
	AMyExplosiveMineItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|OverlapTrap")
	float ExplosionRadius;
};
