// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Loading/LoadingWidget.h"

void UMyGameInstance::OpenLevelWithAsyncLoad(FName LevelName, const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad)
{
	NextLevelName = LevelName;

	// [수정] 누적 시간 0으로 초기화 (가장 중요!)
	TotalElapsedTime = 0.0f;

	// 1. 로딩 위젯 생성 (기존과 동일)
	if (LoadingWidgetClass)
	{
		CurrentLoadingWidget = CreateWidget<ULoadingWidget>(this, LoadingWidgetClass);
		if (CurrentLoadingWidget)
		{
			CurrentLoadingWidget->AddToViewport(9999);
			CurrentLoadingWidget->SetLoadingPercent(0.0f);
		}
	}

	// 2. 비동기 로딩 요청 (기존과 동일)
	if (AssetsToLoad.Num() > 0)
	{
		TArray<FSoftObjectPath> AssetPaths;
		for (const auto& AssetPtr : AssetsToLoad)
		{
			AssetPaths.Add(AssetPtr.ToSoftObjectPath());
		}
		CurrentLoadHandle = StreamableManager.RequestAsyncLoad(AssetPaths);
	}
	else
	{
		CurrentLoadHandle.Reset();
		UE_LOG(LogTemp, Warning, TEXT("[AsyncLoad] 로딩할 에셋 없음. 시간만 채우고 이동합니다."));
	}

	// 3. 타이머 시작 (0.05초마다 실행)
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			ProgressTimerHandle,
			this,
			&UMyGameInstance::UpdateLoadingProgress,
			0.05f,
			true
		);
	}
}

void UMyGameInstance::UpdateLoadingProgress()
{
	// 1. [수정] 시간 직접 누적 (가장 확실한 방법)
	// 0.05초마다 함수가 호출되므로 0.05를 더함
	TotalElapsedTime += 0.05f;

	// 2. 시간 기반 진행률 계산 (MinLoadingTime이 2.0이면 2초 동안 0~1로 증가)
	// MinLoadingTime이 0이면 바로 1.0
	float TimeProgress = (MinLoadingTime > 0.0f) ? (TotalElapsedTime / MinLoadingTime) : 1.0f;

	// 3. 실제 로딩 진행률
	float RealProgress = 1.0f;
	if (CurrentLoadHandle.IsValid())
	{
		RealProgress = CurrentLoadHandle->GetProgress();
	}

	// 4. UI 갱신 (둘 중 느린 쪽 표시)
	float FinalDisplayPercent = FMath::Min(RealProgress, TimeProgress);
	if (CurrentLoadingWidget)
	{
		CurrentLoadingWidget->SetLoadingPercent(FinalDisplayPercent);
	}

	// [디버그 로그] 이게 출력창에 찍혀야 합니다!
	// 예: [Loading] Time: 1.5/2.0, Real: 1.0 -> Wait
	// UE_LOG(LogTemp, Log, TEXT("[Loading] Time: %.2f / %.2f, Real: %.2f"), TotalElapsedTime, MinLoadingTime, RealProgress);

	// 5. 완료 조건 확인
	bool bIsRealLoadingFinished = (!CurrentLoadHandle.IsValid() || CurrentLoadHandle->HasLoadCompleted());
	bool bIsTimeFinished = (TimeProgress >= 1.0f); // 100% 넘었는지 확인

	if (bIsRealLoadingFinished && bIsTimeFinished)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Loading] 로딩 완료! %s 레벨로 이동합니다."), *NextLevelName.ToString());

		// 타이머 정지
		if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(ProgressTimerHandle);
		CurrentLoadHandle.Reset();

		// 레벨 이동
		UGameplayStatics::OpenLevel(this, NextLevelName);
	}
}