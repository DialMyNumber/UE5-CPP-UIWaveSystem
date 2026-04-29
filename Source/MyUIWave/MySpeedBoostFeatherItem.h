#pragma once

#include "CoreMinimal.h"
#include "MyOverlapConsumableItem.h"
#include "MySpeedBoostFeatherItem.generated.h"

UCLASS()
class MYUIWAVE_API AMySpeedBoostFeatherItem : public AMyOverlapConsumableItem
{
	GENERATED_BODY()
	
public:
	AMySpeedBoostFeatherItem();

	virtual void ActivateItem(AActor* Activator) override;

};