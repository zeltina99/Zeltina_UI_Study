// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMenuWidget.h"
#include "UI/Lobby/LobbyMenuWidget.h"
#include "Components/Button.h"

void ULobbyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼에 함수 연결
	if (StageBtn)     StageBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnStageClicked);
	if (ShopBtn)      ShopBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnShopClicked);
	if (CharacterBtn) CharacterBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnCharacterClicked);
	if (EquipmentBtn) EquipmentBtn->OnClicked.AddDynamic(this, &ULobbyMenuWidget::OnEquipmentClicked);
}

void ULobbyMenuWidget::OnStageClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Stage"));
	}
}

void ULobbyMenuWidget::OnShopClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Shop"));
	}
}

void ULobbyMenuWidget::OnCharacterClicked()
{
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Character"));
	}
}

void ULobbyMenuWidget::OnEquipmentClicked()
{	
	if (OnMenuSelected.IsBound())
	{
		OnMenuSelected.Broadcast(FName("Equipment"));
	}
}
