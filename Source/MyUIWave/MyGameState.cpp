#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	Score = 0;	// 스코어 초기화
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	Score += Amount;
}