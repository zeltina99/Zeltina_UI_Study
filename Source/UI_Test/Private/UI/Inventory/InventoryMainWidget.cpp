

#include "UI/Inventory/InventoryMainWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryItemData.h" // 데이터 객체 헤더 필수!
#include "UI/Inventory/InventoryDetailWidget.h"
#include "Components/TileView.h"           // WrapBox 대신 TileView 사용
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Controller/LobbyPlayerController.h"
#include "Framework/Data/InventoryStructs.h"

void UInventoryMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 1. 탭 버튼 바인딩
	if (TabCharacterBtn) TabCharacterBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnCharacterTabClicked);
	if (TabWeaponBtn) TabWeaponBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnWeaponTabClicked);

	// 2. ★ [수정] 파티 슬롯 바인딩 (AddDynamic 사용)
	// 람다 대신, 아까 만든 래퍼 함수를 각각 연결합니다.
	if (PartySlot_0) PartySlot_0->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnPartySlot0_Clicked);
	if (PartySlot_1) PartySlot_1->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnPartySlot1_Clicked);
	if (PartySlot_2) PartySlot_2->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnPartySlot2_Clicked);

	// 3. 상세 패널 이벤트 구독 (느슨한 결합)
	if (WBP_DetailPanel)
	{
		WBP_DetailPanel->OnSwapButtonClicked.AddDynamic(this, &UInventoryMainWidget::OnSwapRequestReceived);
	}

	// 4. ★ [수정] 뒤로가기 버튼 바인딩 (람다 삭제 -> AddDynamic 사용)
	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UInventoryMainWidget::OnBackBtnClicked);
	}

	// 4. 데이터 초기화
	PartyData.Init(nullptr, 3);
	RefreshInventoryList(true);
}

void UInventoryMainWidget::OnInventorySlotClicked(UInventoryItemData* InData)
{
	if (!InData) return;

	// [로직 분기 1] 교체 모드인가? -> 교체 실행
	if (bIsSwapping)
	{
		if (PartyData.IsValidIndex(SelectedPartyIndex))
		{
			// 데이터 교체
			PartyData[SelectedPartyIndex] = InData;

			// UI 갱신
			RefreshPartySlots();

			// 상세창도 교체된 캐릭터로 갱신
			if (WBP_DetailPanel) WBP_DetailPanel->UpdateInfo(InData);

			// 교체 종료
			bIsSwapping = false;
			UE_LOG(LogTemp, Log, TEXT("파티원 교체 완료: %s"), *InData->ID.ToString());
		}
	}
	// [로직 분기 2] 일반 모드 -> 단순 정보 확인
	else
	{
		// 이땐 파티 슬롯 선택을 해제할지 말지는 기획에 따라 다름.
		// 지금은 단순히 정보만 보여줍니다.
		if (WBP_DetailPanel) WBP_DetailPanel->UpdateInfo(InData);
	}
}

void UInventoryMainWidget::OnPartySlotClicked(int32 SlotIndex)
{
	// 슬롯 선택 시 교체 모드 초기화 (안전장치)
	SelectedPartyIndex = SlotIndex;
	bIsSwapping = false;

	UE_LOG(LogTemp, Log, TEXT("Party Slot %d Selected"), SlotIndex);

	// 상세 정보창 갱신
	if (WBP_DetailPanel)
	{
		// 데이터가 있으면 표시, 없으면 nullptr 전달(숨김)
		UInventoryItemData* Data = PartyData.IsValidIndex(SlotIndex) ? PartyData[SlotIndex] : nullptr;
		WBP_DetailPanel->UpdateInfo(Data);
	}
}

void UInventoryMainWidget::OnSwapRequestReceived()
{
	// 파티 슬롯이 선택되지 않았다면 교체 불가
	if (SelectedPartyIndex < 0 || SelectedPartyIndex >= PartyData.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("파티 슬롯을 먼저 선택해주세요."));
		return;
	}

	// 교체 모드 진입
	bIsSwapping = true;
	UE_LOG(LogTemp, Warning, TEXT("교체 모드 활성화! 인벤토리에서 대상을 선택하세요."));
}

void UInventoryMainWidget::RefreshPartySlots()
{
	// 반복되는 코드를 배열로 처리하여 최적화 및 가독성 확보
	TArray<UImage*> Icons = { PartyIcon_0, PartyIcon_1, PartyIcon_2 };

	for (int32 i = 0; i < Icons.Num(); i++)
	{
		if (Icons[i] && PartyData.IsValidIndex(i) && PartyData[i])
		{
			// 데이터가 있으면 이미지 표시
			UInventoryItemData* Data = PartyData[i];
			UTexture2D* IconTex = nullptr;

			if (Data->bIsCharacter && !Data->CharacterData.FaceIcon.IsNull())
				IconTex = Data->CharacterData.FaceIcon.LoadSynchronous();
			else if (!Data->bIsCharacter && !Data->ItemData.Icon.IsNull())
				IconTex = Data->ItemData.Icon.LoadSynchronous();

			if (IconTex)
			{
				Icons[i]->SetBrushFromTexture(IconTex);
				Icons[i]->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else if (Icons[i])
		{
			// 데이터 없으면 숨김 or 기본 이미지
			Icons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInventoryMainWidget::RefreshInventoryList(bool bIsCharacter)
{
	if (!ContentTileView) return;

	ContentTileView->ClearListItems();

	UDataTable* TargetTable = bIsCharacter ? CharacterDataTable : WeaponDataTable;

	if (!TargetTable)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ [InventoryMain] 데이터 테이블이 연결되지 않았습니다! WBP에서 할당해주세요."));
		return;
	}

	// 1. 캐릭터 리스트 처리
	if (bIsCharacter)
	{
		if (TargetTable->GetRowStruct() != FCharacterUIData::StaticStruct())
		{
			UE_LOG(LogTemp, Error, TEXT("❌ [Character] 테이블 구조가 FCharacterUIData가 아닙니다!"));
			return;
		}

		const TMap<FName, uint8*>& RowMap = TargetTable->GetRowMap();
		for (auto& Pair : RowMap)
		{
			FName RowID = Pair.Key;
			FCharacterUIData* Data = reinterpret_cast<FCharacterUIData*>(Pair.Value);

			if (Data)
			{
				UInventoryItemData* NewItem = NewObject<UInventoryItemData>(this);
				// ★ 지원님의 기존 함수 사용: InitCharacter(ID, Data, Owned, Level)
				NewItem->InitCharacter(RowID, *Data, true, 1);
				ContentTileView->AddItem(NewItem);
			}
		}
	}
	// 2. 무기(아이템) 리스트 처리
	else
	{
		if (TargetTable->GetRowStruct() != FItemUIData::StaticStruct())
		{
			UE_LOG(LogTemp, Error, TEXT("❌ [Weapon] 테이블 구조가 FItemUIData가 아닙니다!"));
			return;
		}

		const TMap<FName, uint8*>& RowMap = TargetTable->GetRowMap();
		for (auto& Pair : RowMap)
		{
			FName RowID = Pair.Key;
			FItemUIData* Data = reinterpret_cast<FItemUIData*>(Pair.Value);

			if (Data)
			{
				UInventoryItemData* NewItem = NewObject<UInventoryItemData>(this);
				// ★ 지원님의 기존 함수 사용: InitItem(ID, Data, Owned, EnhanceLevel)
				// 인자 4개를 맞춰서 넣어줍니다. (강화 수치는 일단 0)
				NewItem->InitItem(RowID, *Data, true, 0);
				ContentTileView->AddItem(NewItem);
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("리스트 갱신 완료: %d개"), ContentTileView->GetListItems().Num());

	if (ContentTileView->GetListItems().Num() > 0)
	{
		UInventoryItemData* FirstItem = Cast<UInventoryItemData>(ContentTileView->GetListItems()[0]);
		if (WBP_DetailPanel) WBP_DetailPanel->UpdateInfo(FirstItem);
	}
}

void UInventoryMainWidget::OnBackBtnClicked()
{
	// 컨트롤러에게 "메인 화면(Main)으로 교체해줘"라고 정중하게 요청
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(TEXT("Main")); // ★ 지원님이 만드신 ShowScreen 함수 호출
	}
	else
	{
		// 혹시나 컨트롤러를 못 찾으면 비상 탈출
		RemoveFromParent();
	}
}

void UInventoryMainWidget::OnCharacterTabClicked()
{
	// 1. 캐릭터 리스트로 갱신 (true = Character)
	RefreshInventoryList(true);

	// 2. 탭을 바꿨으니 보고 있던 상세 정보는 끕니다. (하늘색 배경만 나오게)
	if (WBP_DetailPanel)
	{
		WBP_DetailPanel->UpdateInfo(nullptr);
	}

	// 3. (안전장치) 탭을 이동했으므로 진행 중이던 '교체 모드'는 취소합니다.
	bIsSwapping = false;
	SelectedPartyIndex = -1;
}

void UInventoryMainWidget::OnWeaponTabClicked()
{
	// 1. 무기 리스트로 갱신 (false = Weapon)
	RefreshInventoryList(false);

	// 2. 상세 정보 초기화
	if (WBP_DetailPanel)
	{
		WBP_DetailPanel->UpdateInfo(nullptr);
	}

	// 3. 교체 모드 취소
	bIsSwapping = false;
	SelectedPartyIndex = -1;
}
