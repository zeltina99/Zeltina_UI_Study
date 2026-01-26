// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyLobbyWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * @class UMyLobbyWidget
 * @brief 게임의 메인 로비 화면을 관리하는 위젯입니다.
 * @note 재화 표시(골드, 쥬얼)와 메뉴(스테이지, 상점 등)로의 이동을	담당합니다.
 */
UCLASS()
class UI_TEST_API UMyLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

};