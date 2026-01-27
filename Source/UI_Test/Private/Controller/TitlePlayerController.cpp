// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TitlePlayerController.h"
#include "Blueprint/UserWidget.h"

void ATitlePlayerController::BeginPlay()
{
    Super::BeginPlay();
    // 1. WBP_Title 생성해서 화면에 띄움
    if (TitleWidgetClass) {
        UUserWidget* TitleWidget = CreateWidget<UUserWidget>(this, TitleWidgetClass);
        if (TitleWidget) TitleWidget->AddToViewport();
    }

    // 2. 마우스 커서 켜기
    bShowMouseCursor = true;

    // 3. 입력 모드 설정 (UI Only)
    FInputModeUIOnly Mode;
    SetInputMode(Mode);
}
