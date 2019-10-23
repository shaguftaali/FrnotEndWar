// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateRoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDWAR_API UCreateRoomWidget : public UUserWidget
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		void OnStartBtnClicked(FString a_ServerName, bool m_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString a_SessionPassword);
	//void StartOnlineGame(FString a_ServerName, bool m_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString a_SessionPassword);
};
