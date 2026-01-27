// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Loading/LoadingWidget.h"
#include "Components/ProgressBar.h"

void ULoadingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 초기화 시 0%로 설정
	SetLoadingPercent(0.0f);
}

void ULoadingWidget::SetLoadingPercent(float Percent)
{
	// 프로그레스 바 갱신 (텍스트 갱신 로직 삭제됨)
	if (LoadingBar)
	{
		LoadingBar->SetPercent(Percent);
	}
}
	