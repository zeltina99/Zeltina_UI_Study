// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/CurrencyUnitWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCurrencyUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UCurrencyUnitWidget::SetCurrencyData(UTexture2D* Icon, int32 Amount)
{
	// 아이콘 설정
	if (CurrencyIcon && Icon)
	{
		CurrencyIcon->SetBrushFromTexture(Icon);
	}

	// 수량 텍스트 설정
	if (AmountText)
	{
		AmountText->SetText(FText::AsNumber(Amount));
	}
}	