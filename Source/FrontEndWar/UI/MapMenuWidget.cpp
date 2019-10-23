// Fill out your copyright notice in the Description page of Project Settings.


#include "MapMenuWidget.h"
#include "../GameInstance/GameInfoInstance.h"


void UMapMenuWidget::OnCreateRoomBtnClicked()
{
	this->RemoveFromParent();
	Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->ShowCreateRoomMenu();
}

void UMapMenuWidget::OnQuickMatchBtnClicked()
{
	this->RemoveFromParent();
	Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->ShowQuickMatchMenu();
}

void UMapMenuWidget::OnGameListBtnClicked()
{
	this->RemoveFromParent();
	Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->ShowGameListMenu();
}

void UMapMenuWidget::OnAcceptBtnClicked()
{
	this->RemoveFromParent();
	//Cast<UGameInfoInstance>(GetWorld()->GetGameInstance())->
}
