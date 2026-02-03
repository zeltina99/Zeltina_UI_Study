// Source/UI_Test/Private/UI/Lobby/LobbyMenuWidget.cpp

#include "UI/Lobby/LobbyMenuWidget.h"
#include "Components/Button.h"
#include "Controller/LobbyPlayerController.h" // ★ 컨트롤러 통신을 위해 필수

#pragma region 초기화

void ULobbyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. 스테이지 버튼 바인딩
	if (StageBtn)
	{
		StageBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnStageClicked);
	}

	// 2. 소환 버튼 바인딩
	if (SummonBtn)
	{
		SummonBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnSummonClicked);
	}

	// 3. 편성 버튼 바인딩
	if (PartyBtn)
	{
		PartyBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnPartyClicked);
	}

	// 4. 강화 버튼 바인딩
	if (EnhanceBtn)
	{
		EnhanceBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnEnhanceClicked);
	}
}

#pragma endregion 초기화

#pragma region 이벤트 핸들러

void ULobbyMenuWidget::OnStageClicked()
{
	// 1. 이벤트 전파 (선택 사항)
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Stage"));
	}

	// 2. 스테이지 맵 위젯 띄우기 (Lazy Loading 패턴)
	// A. 데이터 유효성 검사
	if (!StageMapClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[LobbyMenu] StageMapClass is NOT set! Check WBP properties."));
		return;
	}

	// B. 인스턴스가 없으면 생성 (최초 1회)
	if (!StageMapInstance)
	{
		StageMapInstance = CreateWidget<UUserWidget>(GetOwningPlayer(), StageMapClass);
	}

	// C. 화면 표시
	if (StageMapInstance)
	{
		if (!StageMapInstance->IsInViewport())
		{
			StageMapInstance->AddToViewport();
		}
		StageMapInstance->SetVisibility(ESlateVisibility::Visible);

		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Opened Stage Map."));
	}
}

void ULobbyMenuWidget::OnSummonClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Summon"));
	}

	// ★ [핵심] 컨트롤러에게 소환 화면 요청 (비동기 로딩 트리거)
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(FName("Summon"));
		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Request 'Summon' Screen -> Controller"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[LobbyMenu] Controller is NOT ALobbyPlayerController!"));
	}
}

void ULobbyMenuWidget::OnPartyClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Party"));
	}

	// 편성 화면 요청 (컨트롤러에 'Party'로 매핑됨)
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(FName("Party"));
		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Request 'Party' Screen"));
	}
}

void ULobbyMenuWidget::OnEnhanceClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Enhance"));
	}

	// 강화 화면 요청 (아직 기능 구현 중이라면 로그 출력)
	UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Enhance Clicked (Feature In Progress)"));
}

#pragma endregion 이벤트 핸들러