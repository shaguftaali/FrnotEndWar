// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRoomData.h"
#include "../GameInstance/GameInfoInstance.h"

void UGameRoomData::JoinRoom(int32 SessionIndex, bool a_IsLAN, bool a_isPresence)
{
	Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->JoinOnlineGame(0, a_IsLAN, a_isPresence);
}
