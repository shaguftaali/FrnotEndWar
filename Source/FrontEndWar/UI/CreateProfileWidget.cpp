// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateProfileWidget.h"
#include "../GameInstance/GameInfoInstance.h"
//#include "../DataSave/PlayerSaveGame.h"


void UCreateProfileWidget::OnOKBtnClicked(FString a_name, int a_language)
{
	if (a_name.IsEmpty()) {
		return;
	}
	UGameInfoInstance* gameInstance = Cast<UGameInfoInstance>(GetWorld()->GetGameInstance());

	UPlayerSaveGame* saveGame = gameInstance->LoadGameData();

	saveGame->playerInfo.name = a_name;

	saveGame->playerInfo.language = static_cast<Language>(a_language);

	gameInstance->SaveGameData(saveGame);

	this->RemoveFromParent();

	gameInstance->ShowMapMenu();
	

}
