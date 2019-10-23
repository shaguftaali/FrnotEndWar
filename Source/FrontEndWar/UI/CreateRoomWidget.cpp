// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateRoomWidget.h"
#include "../GameInstance/GameInfoInstance.h"


void UCreateRoomWidget::OnStartBtnClicked(FString a_ServerName, bool a_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString a_SessionPassword)
{
	UGameInfoInstance* gameInstance = Cast<UGameInfoInstance>(GetWorld()->GetGameInstance());

	gameInstance->StartOnlineGame(a_ServerName, a_IsLAN, a_isPresence, bIsPasswordProtected, a_maxNumPlayers, a_SessionPassword);
}
