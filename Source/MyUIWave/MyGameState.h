#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"


// 레벨에 Row값을 기준으로 40개의 아이템 소환
// 레벨이 시작되면 시간 제한 타이머 시작
// 소환된 아이템 중 코인 아이템을 다 먹었을 경우 시간 제한에 상관 없이 다음 레벨로 이동
// ExplosiveMine 같은 아이템으로 인해 체력이 0이 되면 즉시 게임 오버
// UI - [게임 종료] 이후 처음 레벨부터 [UI - 재시작] 버튼을 누르면 재시작

UCLASS()
class MYUIWAVE_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMyGameState();

	virtual void BeginPlay() override;	// 게임을 시작할 때 초기화

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;	// 현재 레벨 지속시간

	FTimerHandle LevelTimerHandle;	// 현재 레벨의 타이머
	FTimerHandle HUDUpdateTimerHandle;		// HUD의 남은시간 갱신을 위해 매번 UpdateHUD(); 를 호출하면 비효율적
	// UpdateHUD(); 대신 이 타이머를 사용하여 UpdateHUD(); 호출 횟수를 줄이기 위해 사용하는 타이머

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;	// 최고 레벨 단계

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;	// 현재 레벨 단계

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapsNames;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);


	void OnCoinCollected();
	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	void UpdateHUD();
};