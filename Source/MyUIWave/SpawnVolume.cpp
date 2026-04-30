#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;	// ItemDataTable 초기화
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

FMyItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if(!ItemDataTable) return nullptr;
	// 아이템 데이터 테이블이 유효하지 않으면 nullptr 반환 권장

	TArray<FMyItemSpawnRow*> AllRows;	// 각 Row의 시작 주소를 담아두는 TArray
	static const FString ContextString(TEXT("ItemSpawnContext"));
	// 디버깅용 인자

	// ItemDataTable의 모든 Row를 가져와서 AllRows TArray에 저장
	ItemDataTable->GetAllRows(ContextString, AllRows); // 디버깅 용으로 첫번째 인자가 필요함
	// 오류가 발생했을때 이 디버깅용 인자 텍스트가 포함된 문자열이 메시지나 로그에 나타남

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FMyItemSpawnRow* Row : AllRows)	// 차례대로 순회하면서
	{
		if (Row)	// Row가 유효할 때
		{
			TotalChance += Row->SpawnChance;	// 스폰 확률을 더함
		}
	}

	// A = 50%, B = 20%, C = 10%, D = 20% 라고 했을때
	// 0 ~ 50 | 50 ~ 70 | 70 ~ 80 | 80 ~ 100
	// RandValue 의 값이 어떤 구간에 있는지를 확인하고 해당 구간의 아이템 스폰
	// 스폰을 했다면 0으로 초기화를 해줘야함 --- (다음 함수 호출시 초기화)

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (FMyItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;	// 해당 열의 스폰 확률
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;	// 혹시라도 위 for문에서 return이 되지 않았다면 nullptr 반환
}


void ASpawnVolume::SpawnRandomItem()
{
	// 임의의 Row(행)을 가져옴
	if (FMyItemSpawnRow* SelectedRow = GetRandomItem())
	{
		// SelectedRow 의 ItemClass열을 Get() 하는데 TSoftClassPtr 타입으로 가져오기 때문에 UClass* 로 받아야함
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			SpawnItem(ActualClass);	// 직접 구현했던 SpawnItem 함수로 스폰
		}
	}
}