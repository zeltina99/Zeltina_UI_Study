// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 1. 위젯 클래스가 에디터에서 지정되었는지 확인
	if (LobbyWidgetClass)
	{
		// 2. 위젯 생성 (CreateWidget)
		LobbyWidgetInstance = CreateWidget<UUserWidget>(this, LobbyWidgetClass);

		if (LobbyWidgetInstance)
		{
			// 3. 화면에 부착 (Add to Viewport)
			LobbyWidgetInstance->AddToViewport();

			// 4. 입력 모드 설정 (UI 전용 모드)
			// 게임 캐릭터는 안 움직이고, UI 버튼만 클릭되게 함
			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(LobbyWidgetInstance->TakeWidget());
			Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(Mode);

			// 5. 마우스 커서 보이기
			bShowMouseCursor = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LobbyWidgetClass is not set in LobbyPlayerController!"));
	}
}
