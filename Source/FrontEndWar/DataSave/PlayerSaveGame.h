// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */

 UENUM(BlueprintType)
enum class  CountryType :uint8 {
	EU,
	RSS,
	Asia,
	USA,
	AU

};


UENUM(BlueprintType)
enum class  Language :uint8 {
	English,
	Spanish,
	French
};

UENUM(BlueprintType)
enum class  GameMode :uint8 {
	Death_Elimination,
	Flag,
	Team_Match
};




USTRUCT(BlueprintType)
struct FPlayerInfo {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = Data)
	FString name;

	UPROPERTY(VisibleAnywhere, Category = Data)
		CountryType country;

	UPROPERTY(VisibleAnywhere, Category = Data)
		Language language;

	UPROPERTY(VisibleAnywhere, Category = Data)
		FString userID;

	UPROPERTY(VisibleAnywhere, Category = Data)
		uint32 level;

	UPROPERTY(VisibleAnywhere, Category = Data)
		uint32 health;

	UPROPERTY(VisibleAnywhere, Category = Data)
		uint32 gold;

	UPROPERTY(VisibleAnywhere, Category = Data)
		uint32 cash;

	UPROPERTY(VisibleAnywhere, Category = Data)
		uint32 ID;

	//Game Data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
		bool isFirstTimePlay;
};

UCLASS()
class FRONTENDWAR_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static const FString SLOT_NAME;

	static const int32 USER_INDEX;

	UPROPERTY(VisibleAnywhere, Category = Data)
	int a = 0;

	UPROPERTY(VisibleAnywhere, Category = Data)
	FPlayerInfo playerInfo;
};
