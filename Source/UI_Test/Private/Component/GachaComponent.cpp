// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GachaComponent.h"
#include "Framework/Data/InventoryStructs.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UGachaComponent::UGachaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGachaComponent::BeginPlay()
{
	Super::BeginPlay();
	// TODO: SaveGame에서 CurrentPityCount 로드해야 함
	
}

void UGachaComponent::RequestSummon(int32 SummonCount)
{
	// 1. 재화 체크 (보석) -> GameInstance나 PlayerState 연동 필요
	// if (!HasEnoughCurrency(SummonCount * Cost)) return;

	TArray<FGachaResult> FinalResults;

	for (int32 i = 0; i < SummonCount; i++)
	{
		FinalResults.Add(CalculateOneSummon());
	}

	// 2. 결과 알림 (UI가 구독)
	// OnGachaFinished.Broadcast(FinalResults); -> 델리게이트 정의 필요
	// 일단 로그로 확인
	for (const auto& Res : FinalResults)
	{
		UE_LOG(LogTemp, Log, TEXT("가챠 결과: %s (등급: %d)"), *Res.ItemID.ToString(), (int32)Res.Rarity);
	}
}

FGachaResult UGachaComponent::CalculateOneSummon()
{
	FGachaResult Result;
	Result.bIsCharacter = true; // 일단 캐릭터만 뽑는다고 가정

	// 1. 천장 체크
	CurrentPityCount++;
	if (CurrentPityCount >= LegendPityLimit)
	{
		Result.Rarity = EItemRarity::Legendary;
		CurrentPityCount = 0; // 천장 초기화
		UE_LOG(LogTemp, Warning, TEXT("천장 발동! 전설 확정!"));
	}
	else
	{
		// 2. 확률 기반 등급 결정 (Weighted Random)
		// 테이블에서 확률 데이터를 가져와서 계산 (여기선 하드코딩 예시)
		float RandVal = FMath::FRandRange(0.0f, 100.0f);

		if (RandVal <= 1.0f) Result.Rarity = EItemRarity::Legendary; // 1%
		else if (RandVal <= 5.0f) Result.Rarity = EItemRarity::Epic; // 4%
		else if (RandVal <= 20.0f) Result.Rarity = EItemRarity::Rare; // 15%
		else Result.Rarity = EItemRarity::Common; // 나머지
	}

	// 3. 해당 등급의 캐릭터 풀에서 랜덤 1명 선정
	// (DT_Character에서 해당 Rarity인 RowName들을 추려서 랜덤 픽)
	// 로직 구현 필요... 임시로 ID 할당
	Result.ItemID = FName("Char_1");

	// 4. 전설이 나왔으면 천장 초기화 (운 좋게 뽑았을 경우)
	if (Result.Rarity == EItemRarity::Legendary)
	{
		CurrentPityCount = 0;
	}

	// 5. 중복 검사 (InventoryManager와 연동 필요)
	// bool bHas = Inventory->HasCharacter(Result.ItemID);
	// Result.bIsDuplicate = bHas;
	// if (bHas) Result.FragmentAmount = GetFragmentAmountByRarity(Result.Rarity);

	return Result;
}




