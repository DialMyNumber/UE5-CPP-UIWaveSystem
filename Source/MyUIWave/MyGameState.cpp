#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "MyCoinItem.h"			// 코인 아이템을 다 먹었는지 체크할 때 필요

AMyGameState::AMyGameState()
{
	Score = 0;	// 스코어 초기화
	SpawnedCoinCount = 0;	// 코인 초기화
	CollectedCoinCount = 0;	// 코인 초기화
	LevelDuration = 30.0f;	// 레벨 지속시간 초기화
	CurrentLevelIndex = 0;	// 현재 레벨 초기화
	MaxLevels = 3;		// 최대 레벨 초기화
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	Score += Amount;
}

void AMyGameState::OnCoinCollected()
{
	++CollectedCoinCount;
	UE_LOG(LogTemp, Warning, TEXT("Collected Coin : %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}

void AMyGameState::StartLevel()
{
	SpawnedCoinCount = 0;		// 현재 레벨별로 다시 초기화
	CollectedCoinCount = 0;		// 현재 레벨별로 다시 초기화

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	// GetWorld()를 통해 현재 월드에서, SpawnVolume을 찾아서, FoundVolumes에 넣음
	// SpawnVolume이 여러개일수 있으니까

	const int32 ItemToSpawn = 40;

	// 스폰된 코인의 개수 카운트
	for (int32 i = 0; i < ItemToSpawn; ++i) 
	{
		if (FoundVolumes.Num() > 0)	// SpawnVolume이 있을때
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				// 

				// AMyCoinItem 포함 그 하위 자식 클래스인지 확인
				if (SpawnedActor && SpawnedActor->IsA(AMyCoinItem::StaticClass()))
				{
					++SpawnedCoinCount;
				}
			}
		}
	}

	// 현재 레벨 제한시간 작동
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnLevelTimeUp,
		LevelDuration,
		false	// 반복여부
	);

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin:"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void AMyGameState::OnLevelTimeUp()
{
	EndLevel();
}

// 시간 제한이 다 되었거나, 코인을 다 먹었거나 등
void AMyGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);	// 타이머 초기화
	++CurrentLevelIndex;

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapsNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapsNames[CurrentLevelIndex]);
	}
	else // 예외처리
	{
		OnGameOver();
	}
}

void AMyGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
}