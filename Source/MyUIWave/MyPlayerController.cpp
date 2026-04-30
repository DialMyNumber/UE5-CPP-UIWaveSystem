#include "MyPlayerController.h"
#include "MyGameState.h"		// UpdateHUD(); 를 쓰기 위해
#include "MyGameInstance.h"		// StartGame()에 사용
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"	// StartGame()에 사용
#include "Components/TextBlock.h"	//	MainMenu에 사용

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),	// 어차피 블루프린트에서 할당할거긴 하지만 안전하게 nullptr로 초기화
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
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

/* 레벨을 갱신할 때마다 PlayerController가 새로 만들어짐 = 
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
*/
	FString CurrnetMapName = GetWorld()->GetMapName();
	if (CurrnetMapName.Contains("MenuLevel"))	// 현재 레벨이 메뉴 레벨이면
	{
		ShowMainMenu(false);
	}
}

// 이 함수를 이용해서 갱신은 Game State에서
UUserWidget* AMyPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AMyPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)	// 이미 화면이 켜져있으면
	{
		HUDWidgetInstance->RemoveFromParent();	// 뷰포트에서 떼어내기
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)	// 이미 화면이 켜져있으면
	{
		MainMenuWidgetInstance->RemoveFromParent();	// 뷰포트에서 떼어내기
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)	// 메인 메뉴 클래스가 있으면
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);	// 메인 메뉴 인스턴스 생성
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();	// 뷰포트에 MainMenuWidgetInstance 띄우기

			bShowMouseCursor = true;			// 마우스 커서를 보이게 설정
			SetInputMode(FInputModeUIOnly());	// 메인 메뉴상에 있을때 마우스의 포커스를 UI에만 작동하도록
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
	}
}


void AMyPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)	// 이미 화면이 켜져있으면
	{
		HUDWidgetInstance->RemoveFromParent();	// 뷰포트에서 떼어내기
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)	// 이미 화면이 켜져있으면
	{
		MainMenuWidgetInstance->RemoveFromParent();	// 뷰포트에서 떼어내기
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)	// 메인 메뉴 클래스가 있으면
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);	// 메인 메뉴 인스턴스 생성
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();	// 뷰포트에 HUDWidgetInstance 띄우기 = 인게임 내

			bShowMouseCursor = false;			// 마우스 커서를 안보이게 설정
			SetInputMode(FInputModeGameOnly());	// 게임 내부에서만 마우스가 사용되도록(IA_Look)
		}

		// 삼항연산자
		AMyGameState* MyGameState = GetWorld() ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
		if (MyGameState)
		{
			MyGameState->UpdateHUD();	// HUD 갱신
		}
	}
}

void AMyPlayerController::StartGame()
{
	// 게임 인스턴스를 완전히 초기화하기 위해
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		MyGameInstance->CurrentLevelIndex = 0;
		MyGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}