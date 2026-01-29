// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Stage/StageMapWidget.h"
#include "UI/Stage/StageNodeWidget.h"
#include "UI/Stage/StagePopupWidget.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h" // [중요] 위젯 트리 순회를 위해 필요

void UStageMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. 현재 유저의 클리어 정보 가져오기 (나중에는 SaveGame에서 로드)
	// 시작은 1-1만 열려 있음
	int32 ClearStageIndex = 0;

	// 2. 내 자식 위젯들을 전부 뒤져서 'UStageNodeWidget' 타입을 찾는다. (WidgetTree 순회)
	// 기획자가 WBP에 노드를 100개를 박아놔도 여기서 다 찾아냅니다.
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);

	for (UWidget* Widget : AllWidgets)
	{
		if (UStageNodeWidget* Node = Cast<UStageNodeWidget>(Widget))
		{
			// 2-1. 이벤트 연결 (노드가 클릭되면 내 함수 OnNodeClicked 실행해라)
			if (!Node->OnStageSelected.IsBound())
			{
				Node->OnStageSelected.AddDynamic(this, &UStageMapWidget::OnNodeClicked);
			}

			// 2-2. 잠금/해금 상태 초기화
			// (내 번호가 클리어+1 보다 크면 잠금)
			bool bIsLocked = Node->TargetStageIndex > (ClearStageIndex + 1);
			Node->InitializeNode(bIsLocked);

			// 썸네일 이미지 적용 로직
			if (FStageData* Data = GetStageDataByIndex(Node->TargetStageIndex))
			{
				// 1. 이름 설정
				Node->SetStageName(Data->StageName);

				// 2. 아이콘 설정 (함수 이름 변경됨!)
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

void UStageMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized(); // ★ 중요: 부모 초기화 필수

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
