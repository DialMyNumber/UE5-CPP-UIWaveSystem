#include "MyPlayerController.h"
#include "MyGameState.h"		// UpdateHUD(); 를 쓰기 위해
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),	// 어차피 블루프린트에서 할당할거긴 하지만 안전하게 nullptr로 초기화
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetInstance(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// LocalPlayer = 현재 플레이어의 객체
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			// LocalPlayer의 UEnhancedInputLocalPlayerSubsystem 을 가져옴,
			// UEnhancedInputLocalPlayerSubsystem는 IMC를 관리하는 서브 시스템
		{
			if (InputMappingContext) // InputMappingContext 가 존재할 때
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				// AddMappingContext 함수를 통해 0순위로 InputMappingContext 추가
			}
		}
	}

	// Build.cs 에 추가가 필요함
	if (HUDWidgetClass) // 갱신은 Game State에서
	{
		// this = PlayerController에 HUDWidgetClass를 만들어서 HUDWidget에 할당
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();	// 뷰포트에 추가
		}
	}

	// 삼항연산자, GetWorld() 성공시 GetWorld()->GetGameState<AMyGameState>()
	AMyGameState* MyGameState = GetWorld() ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
	if (MyGameState)
	{
		MyGameState->UpdateHUD();
	}
}

// 이 함수를 이용해서 갱신은 Game State에서
UUserWidget* AMyPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance; 
}