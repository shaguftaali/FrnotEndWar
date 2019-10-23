// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DataSave/PlayerSaveGame.h"
#include "SessionResultData.generated.h"

//USTRUCT(BlueprintType)
//struct FSessionlData {
//
//	GENERATED_USTRUCT_BODY()
//};

USTRUCT(BlueprintType)
struct FSessionResutlData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		FString RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		int32 CurrentNumberOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		int32 MaxNumberOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		FString SessionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		GameMode ModeOfGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		bool bIsLAN;


	//====================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		bool bIsPasswordProtected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		FString SessionPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
		int32 Ping;

};

UCLASS()
class FRONTENDWAR_API ASessionResultData : public AActor
{
	GENERATED_BODY()
	
//public:	
//	// Sets default values for this actor's properties
//	ASessionResultData();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
