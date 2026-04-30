#include "MyGameStateBase.h"

AMyGameStateBase::AMyGameStateBase()
{
	Score = 0;	// 스코어 초기화
}

int32 AMyGameStateBase::GetScore() const
{
	return Score;
}

void AMyGameStateBase::AddScore(int32 Amount)
{
	Score += Amount;
}