// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/MyLobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMyLobbyWidget::NativeConstruct()
{
	if (StageBtn)     StageBtn->OnClicked.AddDynamic(this, &UMyLobbyWidget::OnStageClicked);
	if (ShopBtn)      ShopBtn->OnClicked.AddDynamic(this, &UMyLobbyWidget::OnShopClicked);
	if (CharacterBtn) CharacterBtn->OnClicked.AddDynamic(this, &UMyLobbyWidget::OnCharacterClicked);
	if (EquipmentBtn) EquipmentBtn->OnClicked.AddDynamic(this, &UMyLobbyWidget::OnEquipmentClicked);
	if (SettingBtn)   SettingBtn->OnClicked.AddDynamic(this, &UMyLobbyWidget::OnSettingClicked);

	//테스트 용으로 임의로 넣음
	UpdateCurrencies(1500, 500);
}

void UMyLobbyWidget::UpdateCurrencies(int32 Gold, int32 Gem)
{
	if(GoldText)
	{
		// FString::FromInt로 정수를 문자열로 변환
		GoldText->SetText(FText::FromString(FString::FromInt(Gold)));
	}
	if (GemText)
	{
		GemText->SetText(FText::FromString(FString::FromInt(Gem)));
	}
}

void UMyLobbyWidget::OnStageClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Open Stage UI"));
}

void UMyLobbyWidget::OnShopClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Open Shop UI"));
}

void UMyLobbyWidget::OnCharacterClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Open Character Inventory"));	
}

void UMyLobbyWidget::OnEquipmentClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Open Equipment UI"));
}

void UMyLobbyWidget::OnSettingClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Open Settings Popup"));
}
