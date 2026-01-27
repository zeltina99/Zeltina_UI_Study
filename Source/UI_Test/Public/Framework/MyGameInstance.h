// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

class ULoadingWidget;

/**
 * @class UMyGameInstance
 * @brief 게임의 전역 데이터 및 레벨 이동 간의 비동기 로딩을 관리하는 클래스입니다.
 * @details StreamableManager를 사용하여 에셋을 미리 메모리에 로드한 후 OpenLevel을 호출합니다.
 */
UCLASS()
class UI_TEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 전역 에셋 로더 (비동기 로딩 수행 담당).
	 */
	FStreamableManager StreamableManager;

	/**
	 * @brief 지정된 레벨로 이동하기 전, 필요한 에셋들을 비동기로 로딩합니다.
	 * @details 로딩 위젯을 띄우고, 에셋 로딩이 완료되면 OpenLevel을 호출합니다.
	 * @param LevelName 이동할 레벨의 이름 (예: "Lobby")
	 * @param AssetsToLoad 미리 로딩할 에셋들의 경로(SoftObjectPtr) 목록
	 */
	UFUNCTION(BlueprintCallable, Category = "Level System")
	void OpenLevelWithAsyncLoad(FName LevelName, const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad);

protected:
	/**
	 * @brief 로딩 화면 위젯 클래스 (에디터에서 WBP_Loading 할당).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ULoadingWidget> LoadingWidgetClass = nullptr;

private:
	/**
	 * @brief 현재 화면에 떠 있는 로딩 위젯 인스턴스.
	 */
	UPROPERTY()
	TObjectPtr<ULoadingWidget> CurrentLoadingWidget = nullptr;

	/**
	 * @brief 이동할 목표 레벨 이름 임시 저장.
	 */
	FName NextLevelName;

	/**
	 * @brief 현재 진행 중인 비동기 로딩 핸들.
	 * @details 이 핸들을 통해 로딩 진행률(GetProgress)을 확인하고, 로딩을 취소하거나 완료 여부를 확인합니다.
	 */
	TSharedPtr<FStreamableHandle> CurrentLoadHandle = nullptr;

	/**
	 * @brief 진행률 체크를 위한 타이머 핸들.
	 */
	FTimerHandle ProgressTimerHandle;

	/**
	 * @brief 타이머에 의해 주기적으로 호출되어 로딩 진행률을 갱신하는 함수입니다.
	 * @details 로딩이 완료되면 타이머를 정지하고 OpenLevel을 호출합니다.
	 */
	void UpdateLoadingProgress();
};
