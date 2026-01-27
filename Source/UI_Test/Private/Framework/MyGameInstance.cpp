// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Loading/LoadingWidget.h"

void UMyGameInstance::OpenLevelWithAsyncLoad(FName LevelName, const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad)
{
	NextLevelName = LevelName;

	// 1. 로딩 위젯 생성 및 화면 표시
	if (LoadingWidgetClass)
	{
		CurrentLoadingWidget = CreateWidget<ULoadingWidget>(this, LoadingWidgetClass);
		if (CurrentLoadingWidget)
		{
			// 최상단(Z-Order: 9999)에 표시하여 화면을 가림
			CurrentLoadingWidget->AddToViewport(9999);
			CurrentLoadingWidget->SetLoadingPercent(0.0f);
		}
	}

	// 2. 로딩할 에셋이 없다면 즉시 이동 (안전장치)
	if (AssetsToLoad.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AsyncLoad] No assets to load. Opening level immediately."));
		UGameplayStatics::OpenLevel(this, NextLevelName);
		return;
	}

	// 3. TSoftObjectPtr -> FSoftObjectPath 변환 (매니저가 경로를 요구함)
	TArray<FSoftObjectPath> AssetPaths;
	for (const auto& AssetPtr : AssetsToLoad)
	{
		AssetPaths.Add(AssetPtr.ToSoftObjectPath());
	}

	// 4. 비동기 로딩 요청 (RequestAsyncLoad)
	// 로딩을 시작만 하고 함수는 즉시 반환됨 (Non-Blocking)
	CurrentLoadHandle = StreamableManager.RequestAsyncLoad(AssetPaths);

	// 5. 진행률 감시 타이머 시작 (0.05초마다 체크)
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			ProgressTimerHandle,
			this,
			&UMyGameInstance::UpdateLoadingProgress,
			0.05f, // 0.05초 간격
			true   // 반복 실행
		);
	}
}

void UMyGameInstance::UpdateLoadingProgress()
{
	// 핸들이 유효하지 않으면 타이머 정지 (예외 처리)
	if (!CurrentLoadHandle.IsValid())
	{
		if (GetWorld()) 
		{
			GetWorld()->GetTimerManager().ClearTimer(ProgressTimerHandle);
		}
		return;
	}

	// 1. 실제 로딩 진행률 가져오기 (0.0 ~ 1.0)
	const float RealProgress = CurrentLoadHandle->GetProgress();

	// 2. 위젯 업데이트
	if (CurrentLoadingWidget)
	{
		CurrentLoadingWidget->SetLoadingPercent(RealProgress);
	}

	// 3. 로딩 완료 확인 (HasLoadCompleted)
	if (CurrentLoadHandle->HasLoadCompleted())
	{
		UE_LOG(LogTemp, Log, TEXT("[AsyncLoad] Loading Complete. Opening Level: %s"), *NextLevelName.ToString());

		// 타이머 정지
		if (GetWorld()) 
		{
			GetWorld()->GetTimerManager().ClearTimer(ProgressTimerHandle);
		}

		// 핸들 리셋 (선택 사항: OpenLevel시 어차피 정리되나 명시적으로 해제)
		CurrentLoadHandle.Reset();

		// 4. 진짜 레벨 이동
		// 에셋들이 이미 메모리에 올라와 있으므로 OpenLevel 렉이 최소화됨
		UGameplayStatics::OpenLevel(this, NextLevelName);
	}
}
	