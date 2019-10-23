// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameRoomData.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDWAR_API UGameRoomData : public UUserWidget
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		void JoinRoom(int32 SessionIndex, bool a_IsLAN, bool a_isPresence);
	
};
