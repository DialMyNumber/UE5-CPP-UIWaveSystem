#include "MyGameState.h"
#include "MyGameInstance.h"		// Game Instance
#include "MyPlayerController.h"		// HUD에 필요
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "MyCoinItem.h"			// 코인 아이템을 다 먹었는지 체크할 때 필요
#include "Components/TextBlock.h"	// HUD에 필요
#include "Blueprint/UserWidget.h"	// HUD에 필요

// 매 레벨당 초기화가 됨
// 그래서 Game Instance 라는 싱글톤 객체를 이용해서 게임 전체에서 공유

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

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,	// 이 객체에서
		&AMyGameState::UpdateHUD,
		0.1f,
		true	// 반복 여부
	);
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			MyGameInstance->AddToScore(Amount);
			// 게임 인스턴스 싱글톤에 Score 추가
		}
	}
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
	// 레벨을 띄우면 게임 HUD로 전환
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentLevelIndex = MyGameInstance->CurrentLevelIndex;
			// 게임 인스턴스 싱글톤에 있는 CurrentLevelIndex를 가져옴
		}
	}

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

	UpdateHUD();

	// 현재 레벨 제한시간 작동
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnLevelTimeUp,
		LevelDuration,
		false	// 반복여부
	);
}

void AMyGameState::OnLevelTimeUp()
{
	EndLevel();
}

// 시간 제한이 다 되었거나, 코인을 다 먹었거나 등
void AMyGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);  // 타이머 초기화
	++CurrentLevelIndex;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			AddScore(Score);  // 스코어 추가
			MyGameInstance->CurrentLevelIndex = CurrentLevelIndex;
			// 게임 인스턴스 싱글톤에 있는 CurrentLevelIndex를 갱신
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		// 마지막 레벨에 도달하면 게임 오버
		OnGameOver();
		return;
	}

	// 아직 마지막 레벨에 도달하지 않았으면 다음 레벨을 열기
	if (LevelMapsNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapsNames[CurrentLevelIndex]);
	}
	else
	{
		// 예외 처리: 레벨 맵이 존재하지 않으면 게임 오버
		OnGameOver();
	}
}

void AMyGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->ShowMainMenu(true);	// true를 넣어서 Restart로 보이게
		}
	}
}

// HUD를 갱신하는 함수, C++ 함수로 구현하면 필요한 경우에만 함수를 호출해서 업데이트 하면 되기 때문에 성능 개선
void AMyGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = MyPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{															// Widget 에서 이름을 Time이라고 설정해둠
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle); // 남은 시간
					
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{															// Widget 에서 이름을 Score라고 설정해둠
					if (UGameInstance* GameInstance = GetGameInstance())	// 총 점수 합
					{
						UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
						if (MyGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), MyGameInstance->TotalScore)));
						}

					}
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{														// Widget 에서 이름을 Level이라고 설정해둠
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrentLevelIndex + 1)));
				}
			}
		}
	}
}