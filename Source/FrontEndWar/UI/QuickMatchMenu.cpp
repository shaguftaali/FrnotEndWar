// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickMatchMenu.h"
#include "../GameInstance/GameInfoInstance.h"
#include "Engine.h"
//#include "Ei"

void UQuickMatchMenu::OnQuckiBtnClicked(int32 SessionIndex, bool a_IsLAN, bool a_isPresence)
{
	//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("OnQuckiBtnClicked"));
	(Cast<UGameInfoInstance>(GetWorld()->GetGameInstance()))->JoinOnlineGame(SessionIndex, a_IsLAN, a_isPresence);
}
