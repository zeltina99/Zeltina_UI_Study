// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMainWidget.h"
#include "UI/Lobby/LobbyMenuWidget.h"
#include "UI/Lobby/LobbyTopBarWidget.h"	
#include "Controller/LobbyPlayerController.h"

void ULobbyMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기 데이터 갱신
	RefreshLobby();

	// 메뉴바의 이벤트(델리게이트) 구독
	if (WBP_MainMenu)
	{
		// MenuWidget이 버튼이 눌리면 HandleMenuSelection 호출
		WBP_MainMenu->OnMenuSelected.AddDynamic(this, &ULobbyMainWidget::HandleMenuSelection);
	}
}

void ULobbyMainWidget::RefreshLobby()
{
	// TODO: 실제 게임 데이터 연동 필요. 현재는 더미 데이터.
	const int32 MyGold = 50000;
	const int32 MyGem = 1200;

	// 상단바에게 갱신 명령 하달 (직접 텍스트를 고치지 않음)
	if (WBP_TopBar)
	{
		WBP_TopBar->UpdateTopBarInfo(MyGold, MyGem);
	}
}

void ULobbyMainWidget::HandleMenuSelection(FName MenuName)
{
	UE_LOG(LogTemp, Log, TEXT("[LobbyMain] Menu Request: %s"), *MenuName.ToString());

	// 1. 소유자 컨트롤러 캐스팅 (LobbyController인지 확인)
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		// 2. 화면 전환 요청 위임
		PC->ShowScreen(MenuName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[LobbyMain] Owning Player is NOT ALobbyPlayerController!"));
	}
}
