#include "MyBaseItem.h"

AMyBaseItem::AMyBaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}