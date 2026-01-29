// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FStageData.generated.h"

/**
 * @struct FStageData
 * @brief 스테이지 정보를 정의하는 데이터 테이블 행(Row) 구조체입니다.
 * @details 기획자가 엑셀(csv) 또는 에디터의 테이블에서 각 스테이지의 정보를 설정합니다.
 */

USTRUCT(BlueprintType)
struct FStageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief UI에 표시될 스테이지의 이름입니다. (예: "어둠의 숲")
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage|Config")
	FText StageName;

	/**
	 * @brief 팝업 창에 표시될 스테이지 상세 설명입니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage|Config")
	FText Description;

	/**
	 * @brief 실제 로딩할 레벨(Map)의 에셋 이름입니다.
	 * @details OpenLevelWithAsyncLoad 함수에 전달될 식별자입니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	FName LevelToLoad;

	/**
	 * @brief [팝업용] 스테이지 미리보기 대형 이미지
	 * @details TSoftObjectPtr을 사용하여 UI가 열릴 때 메모리에 로드합니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	/**
	 * @brief [지도용] 노드 버튼에 들어갈 작은 아이콘 (예: 1-1 숫자, 해골 마크)
	 * @note ★ 새로 추가된 변수 ★
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TSoftObjectPtr<UTexture2D> NodeIcon;

	/**
	 * @brief 스테이지 순서 및 해금 조건을 판단하는 인덱스입니다.
	 * @details 1-1 스테이지는 인덱스 1, 1-2 스테이지는 인덱스 2, ... 1-5는 5이며,
	 * 유저가 1을 클리어하면 Index가 2인 스테이지가 해금되는 방식이다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	int32 StageIndex;

};
