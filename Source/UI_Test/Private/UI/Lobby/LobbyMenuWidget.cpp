// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMenuWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h" // CreateWidget, AddToViewport 사용을 위해 필요

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

	// 2. 월드맵 위젯 띄우기 로직 (핵심)

	// A. 클래스가 설정되어 있는지 확인 (에디터에서 할당 안 했으면 Crash 방지)
	if (!StageMapClass)
	{
		UE_LOG(LogTemp, Error, TEXT("StageMapClass is NOT set in LobbyMenuWidget!"));
		return;
	}

	// B. 이미 만들어둔 인스턴스가 없다면 새로 생성 (Lazy Loading)
	if (!StageMapInstance)
	{
		StageMapInstance = CreateWidget<UUserWidget>(GetOwningPlayer(), StageMapClass);
	}

	// C. 화면에 띄우기
	if (StageMapInstance)
	{
		// 이미 화면에 있다면 굳이 또 추가하지 않음
		if (!StageMapInstance->IsInViewport())
		{
			StageMapInstance->AddToViewport();
		}

		// 혹시 숨겨져 있었다면 보이게 설정
		StageMapInstance->SetVisibility(ESlateVisibility::Visible);
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
