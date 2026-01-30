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
