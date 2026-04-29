#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// 먼저 박스 컴포넌트의 크기를 구해야함
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();	// 박스 컴포넌트의 중심에서 끝 부분까지 각각 XYZ의 절반 길이
	FVector BoxOrigin = SpawningBox->GetComponentLocation();	// 박스 컴포넌트의 위치 = 박스의 중심

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);	// 박스 크기 내부의 임의 좌표
}

void ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return;	// 방어 코드

	// 마찬가지로 AActor 포함 그 하위 자식 클래스까지 적용 가능
	GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),	// 위치
		FRotator::ZeroRotator	// 회전할지 여부
	);
}