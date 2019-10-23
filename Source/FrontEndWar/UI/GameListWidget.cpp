// Fill out your copyright notice in the Description page of Project Settings.


#include "GameListWidget.h"
#include "../GameInstance/GameInfoInstance.h"

void UGameListWidget::OnSearchBtnClicke(bool bIsLAN)
{
	Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->FindOnlineGames(bIsLAN, true);
}

