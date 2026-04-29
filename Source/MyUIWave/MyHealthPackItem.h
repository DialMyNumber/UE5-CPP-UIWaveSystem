#pragma once

#include "CoreMinimal.h"
#include "MyOverlapConsumableItem.h"
#include "MyHealthPackItem.generated.h"


UCLASS()
class MYUIWAVE_API AMyHealthPackItem : public AMyOverlapConsumableItem
{
	GENERATED_BODY()

public:
	AMyHealthPackItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};