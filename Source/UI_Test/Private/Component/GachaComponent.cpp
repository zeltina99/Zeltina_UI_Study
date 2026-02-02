// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GachaComponent.h"
#include "Framework/Data/GachaStructs.h"
#include "Framework/Data/InventoryStructs.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UGachaComponent::UGachaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UGachaComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO: SaveGame 시스템에서 CurrentPityCount를 로드해야 함.
	CurrentPityCount = 0;
}

#pragma endregion

#pragma region Public API

void UGachaComponent::RequestSummon(int32 SummonCount, EGachaType GachaType)
{
	// 1. 재화 검사 (여기서는 생략, 실제로는 GameInstance->ConsumeGem() 호출)
	// if (!HasEnoughGem(...)) return;

	TArray<FGachaResult> Results;

	// 2. 횟수만큼 반복 계산
	for (int32 i = 0; i < SummonCount; i++)
	{
		FGachaResult NewResult = CalculateOneSummon(GachaType);
		Results.Add(NewResult);
	}

	UE_LOG(LogTemp, Log, TEXT("[Gacha] %d회 소환 완료. 결과 %d개 생성됨."), SummonCount, Results.Num());

	// 3. 결과 방송 (UI 및 연출 시스템이 받음)
	if (OnGachaFinished.IsBound())
	{
		OnGachaFinished.Broadcast(Results);
	}
}

#pragma endregion

#pragma region Internal Logic

FGachaResult UGachaComponent::CalculateOneSummon(EGachaType GachaType)
{
	FGachaResult Result;
	Result.bIsCharacter = (GachaType == EGachaType::Character);

	// --------------------------------------------------------
	// 1. 등급 결정 (천장 or 확률)
	// --------------------------------------------------------
	CurrentPityCount++; // 횟수 증가

	// [천장 발동 체크]
	if (CurrentPityCount >= LEGEND_PITY_LIMIT)
	{
		Result.Rarity = EItemRarity::Legendary;
		CurrentPityCount = 0; // 초기화
		UE_LOG(LogTemp, Warning, TEXT("천장 발동! 전설 확정!"));
	}
	else
	{
		// [확률 계산]
		if (ProbabilityTable)
		{
			float TotalWeight = 0.0f;
			TArray<FGachaProbabilityData*> Rows;
			ProbabilityTable->GetAllRows<FGachaProbabilityData>(TEXT("GachaCalc"), Rows);

			// 전체 가중치 합산
			for (auto* Row : Rows)
			{
				if (Row) TotalWeight += Row->Weight;
			}

			// 랜덤 뽑기 (0 ~ TotalWeight)
			float RandomValue = UKismetMathLibrary::RandomFloatInRange(0.0f, TotalWeight);
			float AccumulatedWeight = 0.0f;

			for (auto* Row : Rows)
			{
				if (!Row) continue;

				AccumulatedWeight += Row->Weight;
				if (RandomValue <= AccumulatedWeight)
				{
					Result.Rarity = Row->Rarity;
					break;
				}
			}
		}
		else
		{
			// 테이블 없으면 기본값
			Result.Rarity = EItemRarity::Common;
		}
	}

	// 전설 뽑았으면 천장 초기화 (운 좋게 뽑은 경우 포함)
	if (Result.Rarity == EItemRarity::Legendary)
	{
		CurrentPityCount = 0;
	}

	// --------------------------------------------------------
	// 2. 등급에 맞는 구체적인 아이템 ID 결정
	// --------------------------------------------------------
	Result.ItemID = PickRandomItemID(Result.Rarity, GachaType);

	return Result;
}

FName UGachaComponent::PickRandomItemID(EItemRarity TargetRarity, EGachaType GachaType)
{
	UDataTable* TargetTable = (GachaType == EGachaType::Character) ? CharacterPoolTable : WeaponPoolTable;

	if (!TargetTable)
	{
		UE_LOG(LogTemp, Error, TEXT("[Gacha] 대상 데이터 테이블이 없습니다!"));
		return NAME_None;
	}

	TArray<FName> ValidIDs;
	const TMap<FName, uint8*>& RowMap = TargetTable->GetRowMap();

	// 테이블을 순회하며 해당 등급인 아이템만 골라냄
	for (auto& Pair : RowMap)
	{
		// 구조체 타입에 따라 분기 (Character vs Item)
		if (GachaType == EGachaType::Character)
		{
			FCharacterUIData* Data = reinterpret_cast<FCharacterUIData*>(Pair.Value);
			if (Data && Data->Rank == TargetRarity)
			{
				ValidIDs.Add(Pair.Key);
			}
		}
		else // Weapon
		{
			FItemUIData* Data = reinterpret_cast<FItemUIData*>(Pair.Value);
			if (Data && Data->Rarity == TargetRarity)
			{
				ValidIDs.Add(Pair.Key);
			}
		}
	}

	// 해당 등급 아이템이 하나도 없으면? (데이터 누락 대비) -> 그냥 아무거나
	if (ValidIDs.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Gacha] 등급 %d에 해당하는 아이템이 테이블에 없습니다."), (int32)TargetRarity);
		return TargetTable->GetRowNames()[0];
	}

	// 후보군 중 랜덤 1개 선택
	int32 RandIdx = UKismetMathLibrary::RandomInteger(ValidIDs.Num());
	return ValidIDs[RandIdx];
}

#pragma endregion



