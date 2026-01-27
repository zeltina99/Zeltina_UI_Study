// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyTopBarWidget.h"
#include "UI/Lobby/CurrencyUnitWidget.h"
#include "Components/Button.h"

void ULobbyTopBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 환경 설정 버튼이 있다면
	if (SettingBtn)
	{
		// 눌렸을 때 OnSettingClicked을 호출
		SettingBtn->OnClicked.AddDynamic(this, &ULobbyTopBarWidget::OnSettingClicked);
	}
}

void ULobbyTopBarWidget::UpdateTopBarInfo(int32 Gold, int32 Gem)
{	
	// 자식 위젯에게 데이터 전달 (위임)
	if (GoldUnitWidget)
	{
		/// TODO: 실제 프로젝트에서는 아이콘을 DataAsset에서 가져와야 함. 현재는 nullptr(기존 유지).
		GoldUnitWidget->SetCurrencyData(GoldIconTexture, Gold);
	}

	if (GemUnitWidget)
	{
		GemUnitWidget->SetCurrencyData(GemIconTexture, Gem);
	}
}

void ULobbyTopBarWidget::OnSettingClicked()
{
	UE_LOG(LogTemp, Log, TEXT("[UI] Setting Button Clicked"));
	// 추후 팝업 위젯 로직 추가
}
