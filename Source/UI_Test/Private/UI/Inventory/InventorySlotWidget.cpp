// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
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

void UInventorySlotWidget::InitCharacterSlot(FName ID, const FCharacterUIData& Data, const FOwnedHeroData* OwnedData)
{
	MyID = ID;
	bIsOwned = (OwnedData != nullptr);

	// 1. 아이콘 로드 및 설정
	if (!Data.FaceIcon.IsNull())
	{
		IconImage->SetBrushFromTexture(Data.FaceIcon.LoadSynchronous());
	}

	// 2. 등급에 따른 테두리 색상 적용
	if (RarityBorder)
	{
		RarityBorder->SetColorAndOpacity(GetRarityColor(Data.Rank));
	}

	// 3. 보유/미보유 상태 분기 처리
	if (bIsOwned)
	{
		// [보유 상태]
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor::White); // 원본 색상
		if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Collapsed); // 자물쇠 숨김
		if (SlotBtn) SlotBtn->SetIsEnabled(true); // 터치 활성화

		// 레벨 표시
		if (LevelText && OwnedData)
		{
			LevelText->SetText(FText::AsNumber(OwnedData->Level));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		// [미보유 상태]
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)); // 어둡게
		if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Visible); // 자물쇠 표시
		if (SlotBtn) SlotBtn->SetIsEnabled(false); // 터치 비활성화

		if (LevelText) LevelText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventorySlotWidget::InitItemSlot(FName ID, const FItemUIData& Data, const FOwnedItemData* OwnedData)
{
	MyID = ID;
	bIsOwned = (OwnedData != nullptr);

	if (!Data.Icon.IsNull())
	{
		IconImage->SetBrushFromTexture(Data.Icon.LoadSynchronous());
	}

	if (RarityBorder)
	{
		RarityBorder->SetColorAndOpacity(GetRarityColor(Data.Rarity));
	}

	if (bIsOwned)
	{
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor::White);
		if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Collapsed);
		if (SlotBtn) SlotBtn->SetIsEnabled(true);

		// 강화 수치 표시 (예: +10)
		if (LevelText && OwnedData)
		{
			FString EnhanceStr = FString::Printf(TEXT("+%d"), OwnedData->EnhancementLevel);
			LevelText->SetText(FText::FromString(EnhanceStr));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
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
		// TODO: 상세 팝업 요청 로직
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