// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * @class ULoadingWidget
 * @brief 비동기 로딩 진행률을 시각적으로 표시하는 위젯 클래스입니다.
 * @details GameInstance에서 계산된 로딩 퍼센트(0.0 ~ 1.0)를 받아 ProgressBar를 갱신합니다.
 */
UCLASS()
class UI_TEST_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** @brief 위젯 초기화 시 호출됩니다. */
	virtual void NativeConstruct() override;

public:
	/**
	 * @brief 로딩 진행률을 설정하고 UI를 갱신합니다.
	 * @param Percent 진행률 (0.0 ~ 1.0 범위)
	 */
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void SetLoadingPercent(float Percent);

private:
	/** 
	 * @brief 로딩 진행 상황을 보여주는 프로그레스 바
	 * @warning 에디터의 위젯 이름과 반드시 일치해야 합니다 (BindWidget).
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> LoadingBar;

};
