

#include "UI/Inventory/InventoryMainWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h" // 데이터 객체 헤더 필수!
#include "Components/TileView.h"           // WrapBox 대신 TileView 사용
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Framework/Data/InventoryStructs.h"

void UInventoryMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 1. 탭 버튼 이벤트 연결
	if (TabCharacterBtn)
	{
		TabCharacterBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnCharacterTabClicked);
	}

	if (TabWeaponBtn)
	{
		TabWeaponBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnWeaponTabClicked);
	}

	// 2. 초기 화면 설정 (처음엔 캐릭터 리스트를 보여줌)
	OnCharacterTabClicked();
}

void UInventoryMainWidget::UpdateDetailInfo(UInventoryItemData* InData)
{
	if (!InData) return;

	// 현재 선택된 아이템 기억
	SelectedItem = InData;

	// 1. 이름 텍스트 갱신
	if (DetailNameText)
	{
		DetailNameText->SetText(FText::FromName(InData->ID));
	}

	// 2. 상세 이미지 갱신 (슬롯 때와 마찬가지로 강제 이미지 모드 적용)
	if (DetailImage)
	{
		UTexture2D* TargetTex = nullptr;

		// 데이터 타입에 따라 텍스쳐 로드
		if (InData->bIsCharacter && !InData->CharacterData.FaceIcon.IsNull())
		{
			TargetTex = InData->CharacterData.FaceIcon.LoadSynchronous();
		}
		else if (!InData->bIsCharacter && !InData->ItemData.Icon.IsNull())
		{
			TargetTex = InData->ItemData.Icon.LoadSynchronous();
		}

		if (TargetTex)
		{
			// ★ 여기도 슬롯과 동일하게 브러시를 직접 생성하여 적용 (안전장치)
			FSlateBrush NewBrush;
			NewBrush.SetResourceObject(TargetTex);
			NewBrush.DrawAs = ESlateBrushDrawType::Image; // 이미지 찌그러짐 방지
			NewBrush.TintColor = FLinearColor::White;

			// 상세창 이미지는 크기를 고정하지 않고, WBP에서 설정한 크기에 맞춤
			DetailImage->SetBrush(NewBrush);
			DetailImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			// 이미지가 없으면 숨김 처리하거나 기본 이미지 표시
			DetailImage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	// 로그 출력 (디버깅용)
	UE_LOG(LogTemp, Log, TEXT("[InventoryMain] Updated Detail Info: %s"), *InData->ID.ToString());
}

void UInventoryMainWidget::OnCharacterTabClicked()
{
	RefreshList(true); // 캐릭터 리스트 로드
}

void UInventoryMainWidget::OnWeaponTabClicked()
{
	RefreshList(false); // 무기 리스트 로드
}

void UInventoryMainWidget::RefreshList(bool bIsCharacter)
{
	if (!ContentTileView) return;

	ContentTileView->ClearListItems();

	// TODO: 실제 게임에서는 GameInstance나 PlayerState에서 보유 목록을 가져와야 합니다.
	// 지금은 테스트를 위해 더미(가짜) 데이터를 생성해서 넣습니다.

	for (int32 i = 1; i <= 10; i++)
	{
		UInventoryItemData* NewItem = NewObject<UInventoryItemData>(this);

		if (bIsCharacter)
		{
			// 캐릭터 테스트 데이터
			NewItem->ID = FName(*FString::Printf(TEXT("Char_%d"), i));
			NewItem->bIsCharacter = true;
			NewItem->bIsOwned = (i % 2 != 0); // 홀수 번호만 보유 중 처리 (테스트)
			NewItem->Level = i * 10;
			// 텍스쳐는 데이터 테이블 연결 전이라 비워둠 (흰색 박스 나올 수 있음)
		}
		else
		{
			// 무기 테스트 데이터
			NewItem->ID = FName(*FString::Printf(TEXT("Weapon_%d"), i));
			NewItem->bIsCharacter = false;
			NewItem->bIsOwned = true;
			NewItem->EnhancementLevel = i;
		}

		ContentTileView->AddItem(NewItem);
	}

	// 리스트 갱신 후 첫 번째 아이템 정보를 자동으로 상세창에 띄워주면 좋습니다.
	if (ContentTileView->GetListItems().Num() > 0)
	{
		UpdateDetailInfo(Cast<UInventoryItemData>(ContentTileView->GetListItems()[0]));
	}
}