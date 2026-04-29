#pragma once

#include "CoreMinimal.h"
#include "MyOverlapConsumableItem.h"
#include "MyDizzyMushroomItem.generated.h"

UCLASS()
class MYUIWAVE_API AMyDizzyMushroomItem : public AMyOverlapConsumableItem
{
	GENERATED_BODY()
	
public:
	AMyDizzyMushroomItem();

	virtual void ActivateItem(AActor* Activator) override;

};