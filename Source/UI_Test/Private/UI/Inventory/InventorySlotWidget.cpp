// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// [Event Binding] 버튼 클릭 이벤트 연결
	if (SlotBtn)
	{
		SlotBtn->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClicked);
	}
}

// ★ Tile View가 데이터를 갱신할 때 호출하는 핵심 함수
void UInventorySlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryItemData* Data = Cast<UInventoryItemData>(ListItemObject);
	if (!Data) return;

	// 내 멤버 변수 갱신
	MyID = Data->ID;
	bIsOwned = Data->bIsOwned;

	// 1. 캐릭터 데이터 처리
	if (Data->bIsCharacter)
	{
		// ★ [디버깅용 로그 추가] 도대체 무슨 경로를 로딩하려고 하는지 찍어보자!
		UE_LOG(LogTemp, Warning, TEXT("[InventorySlot] Loading Icon for %s: Path = %s"),
			*MyID.ToString(),
			*Data->CharacterData.FaceIcon.ToString());

		if (!Data->CharacterData.FaceIcon.IsNull())
		{
			IconImage->SetBrushFromTexture(Data->CharacterData.FaceIcon.LoadSynchronous());
		}

		if (RarityBorder)
		{
			RarityBorder->SetColorAndOpacity(GetRarityColor(Data->CharacterData.Rank));
		}

		if (bIsOwned && LevelText)
		{
			LevelText->SetText(FText::AsNumber(Data->Level));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	// 2. 아이템 데이터 처리
	else
	{
		if (!Data->ItemData.Icon.IsNull())
		{
			IconImage->SetBrushFromTexture(Data->ItemData.Icon.LoadSynchronous());
		}

		if (RarityBorder)
		{
			RarityBorder->SetColorAndOpacity(GetRarityColor(Data->ItemData.Rarity));
		}

		if (bIsOwned && LevelText)
		{
			FString EnhanceStr = FString::Printf(TEXT("+%d"), Data->EnhancementLevel);
			LevelText->SetText(FText::FromString(EnhanceStr));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
	}

	// 3. 공통: 보유 여부에 따른 UI 상태 변경 (잠금 처리)
	if (bIsOwned)
	{
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor::White);
		if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Collapsed);
		if (SlotBtn) SlotBtn->SetIsEnabled(true);
	}
	else
	{
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f));
		if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Visible);
		if (SlotBtn) SlotBtn->SetIsEnabled(false);
		if (LevelText) LevelText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventorySlotWidget::OnClicked()
{
	if (bIsOwned)
	{
		UE_LOG(LogTemp, Log, TEXT("[Inventory] Item Selected: %s"), *MyID.ToString());
		// TODO: 여기서 메인 위젯이나 컨트롤러에게 "나 클릭됐어!"라고 알려주는 로직 추가 예정
	}
}

FLinearColor UInventorySlotWidget::GetRarityColor(EItemRarity Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::Common:    return FLinearColor(0.6f, 0.6f, 0.6f); // 회색
	case EItemRarity::Uncommon:  return FLinearColor(0.2f, 1.0f, 0.2f); // 녹색
	case EItemRarity::Rare:      return FLinearColor(0.2f, 0.2f, 1.0f); // 파랑
	case EItemRarity::Epic:      return FLinearColor(0.6f, 0.2f, 1.0f); // 보라
	case EItemRarity::Legendary: return FLinearColor(1.0f, 0.8f, 0.0f); // 금색
	default:                     return FLinearColor::White;
	}
}