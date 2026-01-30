// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h"
#include "UI/Inventory/InventoryMainWidget.h"
#include "Components/Border.h"
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

	// 1. 데이터 캐싱
	MyID = Data->ID;
	bIsOwned = Data->bIsOwned;

	// 2. 각 기능별 함수 호출 (분업화)
	UpdateIcon(Data);    // 그림 그려!
	UpdateVisuals(Data); // 글씨 써!
	UpdateState(bIsOwned); // 버튼 켜/꺼!
}

void UInventorySlotWidget::UpdateIcon(UInventoryItemData* Data)
{
	if (!IconImage) return;

	UTexture2D* TargetIcon = nullptr;

	// 데이터 타입에 따라 아이콘 로드
	if (Data->bIsCharacter)
	{
		if (!Data->CharacterData.FaceIcon.IsNull())
			TargetIcon = Data->CharacterData.FaceIcon.LoadSynchronous();
	}
	else
	{
		if (!Data->ItemData.Icon.IsNull())
			TargetIcon = Data->ItemData.Icon.LoadSynchronous();
	}

	// 아이콘 적용 (강제 이미지 모드)
	if (TargetIcon)
	{
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(TargetIcon);
		NewBrush.ImageSize = FVector2D(210.f, 340.f); // ★ 210x340 크기 적용!
		NewBrush.DrawAs = ESlateBrushDrawType::Image; // ★ 강제 Image 모드
		NewBrush.TintColor = FLinearColor::White;

		IconImage->SetBrush(NewBrush);

		// 초기화 (투명도 등)
		IconImage->SetColorAndOpacity(FLinearColor::White);
		IconImage->SetRenderOpacity(1.0f);
		IconImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		// 데이터 없음 (에러 표시: 빨강)
		IconImage->SetColorAndOpacity(FLinearColor::Red);
	}
}

void UInventorySlotWidget::UpdateVisuals(UInventoryItemData* Data)
{
	if (RarityBorder)
	{
		EItemRarity Rarity = Data->bIsCharacter ? Data->CharacterData.Rank : Data->ItemData.Rarity;
		RarityBorder->SetBrushColor(GetRarityColor(Rarity));
		RarityBorder->SetContentColorAndOpacity(FLinearColor::White);
	}

	// B. 레벨 텍스트 표시
	if (LevelText)
	{
		if (bIsOwned)
		{
			int32 LevelVal = Data->bIsCharacter ? Data->Level : Data->EnhancementLevel;
			FString LevelStr = Data->bIsCharacter ?
				FText::AsNumber(LevelVal).ToString() :
				FString::Printf(TEXT("+%d"), LevelVal);

			LevelText->SetText(FText::FromString(LevelStr));
			LevelText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			LevelText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UInventorySlotWidget::UpdateState(bool bOwned)
{
	// A. 자물쇠 오버레이 (이제 안 씀 -> 숨김)
	if (LockOverlay) LockOverlay->SetVisibility(ESlateVisibility::Collapsed);

	// B. 보유 상태 처리
	if (bOwned)
	{
		// [보유 중] 밝게 표시, 버튼 활성
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor::White);

		if (SlotBtn)
		{
			SlotBtn->SetVisibility(ESlateVisibility::Visible);
			SlotBtn->SetIsEnabled(true);
		}
	}
	else
	{
		// [미보유] 어둡게 표시(Dimmed), 버튼 비활성
		if (IconImage) IconImage->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));

		if (SlotBtn)
		{
			SlotBtn->SetVisibility(ESlateVisibility::Visible);
			SlotBtn->SetIsEnabled(false);
		}
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