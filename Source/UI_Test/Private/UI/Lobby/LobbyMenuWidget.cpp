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
	// 1. 이벤트 방송 (필요시 사용)
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Stage"));
	}

	// 2. [SRP 준수] 컨트롤러에게 화면 전환 위임 (직접 생성 X)
	// 컨트롤러가 ShowScreen을 통해 기존 위젯을 제거하고 StageMap을 띄워줍니다. -> 겹침 해결
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(FName("StageMap"));
		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Request 'StageMap' Screen via Controller."));
	}
}

void ULobbyMenuWidget::OnSummonClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Summon"));
	}

	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(FName("Summon"));
		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Request 'Summon' Screen via Controller."));
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

	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(FName("Enhance"));
		UE_LOG(LogTemp, Log, TEXT("[LobbyMenu] Request 'Enhance' Screen via Controller."));
	}
}

#pragma endregion 이벤트 핸들러