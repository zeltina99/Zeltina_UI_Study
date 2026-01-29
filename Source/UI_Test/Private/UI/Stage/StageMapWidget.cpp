// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Stage/StageMapWidget.h"
#include "UI/Stage/StageNodeWidget.h"
#include "UI/Stage/StagePopupWidget.h"
#include "Framework/MyGameInstance.h"
#include "Components/PanelWidget.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h" // [중요] 위젯 트리 순회를 위해 필요

void UStageMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. 현재 유저의 클리어 정보 가져오기 (나중에는 SaveGame에서 로드)
	// 시작은 1-1만 열려 있음
	int32 CurrentClearIndex = 0;
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
	{
		CurrentClearIndex = GI->MaxClearedStageIndex;
	}

	if (NodeContainer)
	{
		const int32 ChildCount = NodeContainer->GetChildrenCount();

		for (int32 i = 0; i < ChildCount; ++i)
		{
			UWidget* Child = NodeContainer->GetChildAt(i);

			if (UStageNodeWidget* Node = Cast<UStageNodeWidget>(Child))
			{
				// 2-2. 잠금/해금 상태 초기화
				// (내 번호가 클리어+1 보다 크면 잠금)
				const bool bIsLocked = Node->TargetStageIndex > (CurrentClearIndex + 1);
				Node->InitializeNode(bIsLocked);

				// 썸네일 및 아이콘 적용 로직
				if (FStageData* Data = GetStageDataByIndex(Node->TargetStageIndex))
				{
					// 1. 이름 설정 (예: "1-1")
					Node->SetStageName(Data->StageName);

					// 2. 아이콘 설정 (데이터가 존재할 경우에만)
					if (!Data->NodeIcon.IsNull())
					{
						UTexture2D* LoadedIcon = Data->NodeIcon.LoadSynchronous();
						if (LoadedIcon)
						{
							Node->SetNodeIcon(LoadedIcon);
						}
					}
				}
			}
		}
	}
	
}

void UStageMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized(); // ★ 중요: 부모 초기화 필수

	// 전체 위젯 트리를 뒤지는 GetAllWidgets 대신, 지정된 컨테이너의 자식만 순회합니다. (O(N) -> O(1))
	if (NodeContainer)
	{
		const int32 ChildCount = NodeContainer->GetChildrenCount();

		for (int32 i = 0; i < ChildCount; ++i)
		{
			// 컨테이너의 i번째 자식을 가져옵니다.
			UWidget* ChildWidget = NodeContainer->GetChildAt(i);

			// 해당 자식이 스테이지 노드인지 확인합니다.
			if (UStageNodeWidget* Node = Cast<UStageNodeWidget>(ChildWidget))
			{
				// 클릭 이벤트가 아직 바인딩되지 않았을 경우에만 연결합니다. (Safe Guard)
				if (!Node->OnStageSelected.IsBound())
				{
					Node->OnStageSelected.AddDynamic(this, &UStageMapWidget::OnNodeClicked);
				}
			}
		}
	}

	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UStageMapWidget::OnBackClicked);
	}
}

void UStageMapWidget::OnBackClicked()
{
	// 화면에서 이 위젯(StageMap)을 치워버립니다.
	// 그러면 뒤에 깔려있던 로비(Lobby)가 다시 짠 하고 보입니다.
	RemoveFromParent();
}

void UStageMapWidget::OnNodeClicked(int32 StageIndex)
{
	// 1. 데이터 테이블이 없거나 팝업 클래스가 없으면 중단 (안전장치)
	if (!StageDataTable || !PopupClass)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable or PopupClass is missing in WorldMapWidget!"));
		return;
	}

	// 2. 인덱스로 데이터 찾기
	FStageData* RowData = GetStageDataByIndex(StageIndex);
	if (!RowData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find stage data for Index: %d"), StageIndex);
		return;
	}

	// 3. 팝업 위젯 생성 및 띄우기
	if (UStagePopupWidget* Popup = CreateWidget<UStagePopupWidget>(GetOwningPlayer(), PopupClass))
	{
		Popup->UpdatePopupInfo(*RowData); // 데이터 전달
		Popup->AddToViewport(); // 화면에 표시
	}
}

FStageData* UStageMapWidget::GetStageDataByIndex(int32 Index)
{
	// 데이터 테이블의 모든 행(Row)을 가져옴
	static const FString ContextString(TEXT("Stage Data Context"));
	TArray<FStageData*> AllRows;
	StageDataTable->GetAllRows<FStageData>(ContextString, AllRows);

	// 반복문으로 Index가 일치하는 행을 찾음
	for (FStageData* Row : AllRows)
	{
		if (Row && Row->StageIndex == Index)
		{
			return Row;
		}
	}

	return nullptr;
}
