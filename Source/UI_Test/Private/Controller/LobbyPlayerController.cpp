// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Framework/MyGameInstance.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());

	// 1. "무엇을 띄울지" 결정 (여기선 아직 로딩 안 함, 주소만 결정)
	TSoftClassPtr<UUserWidget> TargetSoftClass = MainMenuWidgetClass;

	if (GI && GI->NextLobbyScreen == FName("StageMap"))
	{
		// 맵을 띄워야 한다면 맵 주소로 변경
		if (!StageMapWidgetClass.IsNull())
		{
			TargetSoftClass = StageMapWidgetClass;
		}
		GI->NextLobbyScreen = FName("Main");
	}

	// 2. 결정된 녀석만 "진짜 로딩" (동기 로드)
	// (MainMenu를 띄울 땐 StageMap은 메모리에 안 올라감! -> 최적화 성공)
	if (!TargetSoftClass.IsNull())
	{
		UClass* WidgetClass = TargetSoftClass.LoadSynchronous(); // ★ 여기서 로딩!

		if (WidgetClass)
		{
			CurrentWidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);
			if (CurrentWidgetInstance)
			{
				CurrentWidgetInstance->AddToViewport();

				// 4. 입력 모드 설정
				FInputModeUIOnly Mode;
				Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				SetInputMode(Mode);
				bShowMouseCursor = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TargetClass is NULL! Check PC_Lobby Blueprint settings."));
		}
	}
}

void ALobbyPlayerController::ShowScreen(FName ScreenName)
{
	// 문자열(Name) 비교를 통해 어떤 위젯을 띄울지 결정
	if (ScreenName == "Main")
	{
		ChangeWidget(MainMenuWidgetClass);
	}
	else if (ScreenName == "StageMap") // 배틀/스테이지
	{
		ChangeWidget(StageMapWidgetClass);
	}
	else if (ScreenName == "Formation") // 편성 (인벤토리)
	{
		ChangeWidget(InventoryWidgetClass);
	}
	else if (ScreenName == "Summon") // 소환 (미구현)
	{
		UE_LOG(LogTemp, Warning, TEXT("[LobbyController] Summon UI Not Implemented yet!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[LobbyController] Unknown Screen Name: %s"), *ScreenName.ToString());
	}
}

void ALobbyPlayerController::ChangeWidget(TSoftClassPtr<UUserWidget> NewWidgetClass)
{
	// 1. 유효성 검사
	if (NewWidgetClass.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("[LobbyController] Widget Class is NULL! Check Blueprint Settings."));
		return;
	}

	// 2. 기존 위젯 정리 (메모리 관리 및 화면 겹침 방지)
	if (CurrentWidgetInstance)
	{
		CurrentWidgetInstance->RemoveFromParent();
		CurrentWidgetInstance = nullptr;	
	}

	// 3. 동기 로드 및 생성
	// (규모가 커지면 비동기 로드 StreamableManager 권장)
	UClass* WidgetClass = NewWidgetClass.LoadSynchronous();
	if (WidgetClass)
	{
		CurrentWidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);
		if (CurrentWidgetInstance)
		{
			CurrentWidgetInstance->AddToViewport();

			// 4. 입력 모드 설정 (UI 전용 모드)
			FInputModeUIOnly Mode;
			Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(Mode);
			bShowMouseCursor = true;
		}
	}
}
