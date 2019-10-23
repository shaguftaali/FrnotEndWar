// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfoInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "Templates//SharedPointer.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"


void UGameInfoInstance::BindDelegates()
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnStartOnlineGameComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnJoinSessionComplete);
	OnFindSessionCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnFindSessionsComplete);
}

void UGameInfoInstance::InitiateSetUp()
{
	UWorld* world = GetWorld();
	playerController = UGameplayStatics::GetPlayerController(world, 0);
	BindDelegates();
	CheckForSavedGame();
}


void UGameInfoInstance::CheckForSavedGame()
{
	UPlayerSaveGame* playerSaveGame = LoadGameData();

	if (playerSaveGame == nullptr) {
		SaveGameData(playerSaveGame);
		
	}
	if (playerSaveGame->playerInfo.name.IsEmpty()) {

		ShowCreateProfileMenu();
	}
	else {
		ShowMapMenu();
	}
}

void UGameInfoInstance::ShowCreateProfileMenu()
{
	UCreateProfileWidget* createProfileWB = CreateWidget<UCreateProfileWidget>(playerController,CreateProfileClass);
	createProfileWB->AddToViewport();
	playerController->bShowMouseCursor = true;
}

void UGameInfoInstance::ShowMapMenu()
{
	UMapMenuWidget* mapMenuWB = CreateWidget<UMapMenuWidget>(playerController, MapMenuClass);
	mapMenuWB->AddToViewport();
	playerController->bShowMouseCursor = true;
}

void UGameInfoInstance::ShowCreateRoomMenu()
{
	UCreateRoomWidget* createRoomWB = CreateWidget<UCreateRoomWidget>(playerController, CreateRoomClass);
	createRoomWB->AddToViewport();
	playerController->bShowMouseCursor=true;
}

void UGameInfoInstance::ShowLoadingScreen()
{
}

void UGameInfoInstance::ShowQuickMatchMenu()
{
	UQuickMatchMenu* quickMatchWB = CreateWidget<UQuickMatchMenu>(playerController, QuickMatchClass);
	quickMatchWB->AddToViewport();
	playerController->bShowMouseCursor = true;
}

void UGameInfoInstance::ShowGameListMenu()
{
	//UGameListWidget* 
	gameListWB = CreateWidget<UGameListWidget>(playerController, GameListClass);
	gameListWB->AddToViewport();
	playerController->bShowMouseCursor = true;
}

void UGameInfoInstance::SaveGameData(UPlayerSaveGame* a_gameData)
{
	if (a_gameData == nullptr) {
		a_gameData = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	}

	UGameplayStatics::SaveGameToSlot(a_gameData, UPlayerSaveGame::SLOT_NAME, UPlayerSaveGame::USER_INDEX);
}

void UGameInfoInstance::LaunchLobby(FString ServerName, bool EnableLan)
{
	//IOnlineS
}

UPlayerSaveGame * UGameInfoInstance::LoadGameData()
{
	UPlayerSaveGame* loadedData = Cast<UPlayerSaveGame> (UGameplayStatics::LoadGameFromSlot(UPlayerSaveGame::SLOT_NAME, UPlayerSaveGame::USER_INDEX));
	return loadedData;
}

void UGameInfoInstance::StartOnlineGame(FString a_ServerName, bool m_IsLAN, bool a_IsPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString a_SessionPassword)
{
	// Creating a local player where we can get the UserID from
	ULocalPlayer* const Player = GetFirstGamePlayer();

	HostSession(Player->GetPreferredUniqueNetId().GetUniqueNetId(), GameSessionName, a_ServerName, m_IsLAN, a_IsPresence, bIsPasswordProtected, a_maxNumPlayers, a_SessionPassword);
}

void UGameInfoInstance::FindOnlineGames(bool a_IsLAN, bool a_isPresence)
{
	ULocalPlayer* const Player = GetFirstGamePlayer();
	FindSessions(Player->GetPreferredUniqueNetId().GetUniqueNetId(), GameSessionName,a_IsLAN, a_isPresence);
}



void UGameInfoInstance::JoinOnlineGame(int32 SessionIndex, bool a_IsLAN, bool a_isPresence)
{
	ULocalPlayer* const Player = GetFirstGamePlayer();

	FOnlineSessionSearchResult SearchResult;

	SearchResult = SessionSearch->SearchResults[SessionIndex];


	JoinSession(Player->GetPreferredUniqueNetId().GetUniqueNetId(), GameSessionName, SearchResult);
}

bool UGameInfoInstance::HostSession(TSharedPtr<const FUniqueNetId> a_userID, FName a_SessionName, FString a_ServerName, bool a_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString SessionPassword) {
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Host Session"));
	//Get the online subsystem to work with
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	//FString rm = "server name: " + a_ServerName;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, rm);
	if (OnlineSub) {

		//Get the Session Inteface so we can call the "CreateSession" function on it
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid() && a_userID.IsValid()) {
			/*
				Fill all the Session Setting that we want to use.
			*/

			SessionSettings = MakeShareable<>(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = a_IsLAN;
			SessionSettings->bUsesPresence = a_isPresence;
			SessionSettings->NumPublicConnections = a_maxNumPlayers;
			MaxPlayersInSession = a_maxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			//setting a value in the FOnlineSessionSettings settingd array
			SessionSettings->Set(SETTING_MAPNAME, LobbyMapName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

			//Making a temporary FOnlineSessionSetting variable to hold the data we want to add to the FOnlineSessionSetting's setting array
			FOnlineSessionSetting ExtraSessionSetting;
			ExtraSessionSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;

			//setting the tempory data to the ServerName we got from UMG
			ExtraSessionSetting.Data = a_ServerName;
			SessionSettings->Settings.Add(SETTING_SERVER_NAME, ExtraSessionSetting);

			
			
			

			////setting the temporary data to the bIsPasswordProtected we got from UMG
			//ExtraSessionSetting.Data = bIsPasswordProtected;
			////adding the bIsPasswordProtected value in the FOnlineSessionSetting 's settings array using the key defined in header
			//SessionSettings->Settings.Add(SETTING_SERVER_IS_PROTECTED, ExtraSessionSetting);

			//=====================LATER============================
			////setting the temporary data to the Password we got from UMG
			//ExtraSessionSetting.Data = a_SessionPassword;
			////adding the Password value in the FOnlineSessionSetting 's settings array using the key defined in header
			//SessionSettings->Settings.Add(SETTING_SERVER_PROTECT_PASSWORD, ExtraSessionSetting);



			//Set the delegate to the Handle of the SessionInterface
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			//Our delegate should get called when this is complete (doesn't need to be successful!)
			return Sessions->CreateSession(*a_userID, a_SessionName, *SessionSettings);


		}

		else{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsystem found!"));

		}

	}
		return false;

}



	void UGameInfoInstance::OnCreateSessionComplete(FName a_SesseionName, bool a_WasSuccessful) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *a_SesseionName.ToString(), a_WasSuccessful));

		//Get the OnlineSubsystem so we can get the Session function
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub) {
			
			//Get the Session Interface to call the StartSesion function
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

			if (Sessions.IsValid()) {

				//Clear the SessionComplete delegate handle, since we finished this call;
				Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
				if (a_WasSuccessful) {
					//Set the StartSession delegate handle
					OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

					//Our StartSessionComplete delegate should get called after this
					Sessions->StartSession(a_SesseionName);
				}
			}
		}
	}

	void UGameInfoInstance::OnStartOnlineGameComplete(FName a_SessionName, bool a_WasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *a_SessionName.ToString(), a_WasSuccessful));

		//Get the Online Subsystem so we can get the Session Interface
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

		if (OnlineSub) {

			// Get the Session Interface to clear the Delegate
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid()) {
				// Clear the delegate, since we are done with this call
				Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
			}
		}

		if (a_WasSuccessful) {
			UGameplayStatics::OpenLevel(GetWorld(), LobbyMapName, true, "listen");
		}

		//GetFirstGamePlayer()
	}

	

	bool UGameInfoInstance::JoinSession(TSharedPtr<const FUniqueNetId> a_UserID, FName a_SessionName, const FOnlineSessionSearchResult& a_SearchResult)
	{

		//Return bool
		bool bSuccessful = false;

		//Get OnlineSubsystem we want to work with
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

		if (OnlineSub) {
			//Get SessionInterface from the OnlineSubsystem 
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

			if (Sessions.IsValid() && a_UserID.IsValid()) {

				//Set Handle again
				OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

				//Call the "Join Session" Function with the passed "SearchResult". The "SessionSearch->SearchResults" can be used to get such 
				bSuccessful = Sessions->JoinSession(*a_UserID, a_SessionName, a_SearchResult);

			}

		}
		return bSuccessful;
	}

	void UGameInfoInstance::OnJoinSessionComplete(FName a_SessionName, EOnJoinSessionCompleteResult::Type a_Result)
	{
		//Get OnlineSubsystem we want to work with
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		
		if (OnlineSub) {
			//Get SessionInterface from the OnlineSubsystem
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

			if (Sessions.IsValid()) {

				Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

				//Get the first local playerController, so we can call "Client Travel" to get to the Server Map
				//This is something the Blueprint Node "Join Session does automatically!;

				APlayerController* const PlayerController = GetFirstLocalPlayerController();

				/*We need a FString to use ClientTravel and we can let the SessionInterface contruct such a
				  String for us by giving him the SessionName and an empty String. We want to do this, beacuse
				  Every OnlineSubSystem uses different TravelURLs
				*/

				FString TravelURL;

				if (PlayerController && Sessions->GetResolvedConnectString(a_SessionName, TravelURL)) {
					//Finally call the Client Travel. If you want, you could print the TravelURL to see how it really looks like
					PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
				}
			}
		}
	}

	void UGameInfoInstance::FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName,bool bIsLAN, bool bIsPresence)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("FindSessions"));
		//Get the OnlineSubsystem we want to work with
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

		if (OnlineSub) {
			//Get the SessionInterface from our OnlineSubsystem
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

			if (Sessions.IsValid() && UserId.IsValid()) {
				/*Fill in all the SearchSettings, like if we are searching for a LAN hame and how many results we want to have*/
				SessionSearch = MakeShareable(new FOnlineSessionSearch());

				SessionSearch->bIsLanQuery = bIsLAN;

				SessionSearch->MaxSearchResults = 20;
				SessionSearch->PingBucketSize = 50;

				

				//We only want to set this Query Setting if "bIsPresence" is true
				if (bIsPresence) {
					SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
				}

				TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

				//Set the Delegate to the Delegate Handle of the FindSession function
				OnFindSessionCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegate);

				//Finally call the SessionInterface function. The Delegate gets called once this is finished
				Sessions->FindSessions(*UserId, SearchSettingsRef);

				//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("FindSessions goes well"));
			}
		}
		else {
			//If something goes wrong, just call the Delegate Function directly with "false."
			OnFindSessionsComplete(false);
		}
	}

	void UGameInfoInstance::OnFindSessionsComplete(bool bWasSuccessful)
	{	

		//Get OnlineSubsystem we want to work with
		IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub) {

			//Get SessionIerface of the OnlineSubsystem
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid()) {
				//Clear the Delegate handle, since we finished this call
				Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);

				TArray<FSessionResutlData> SessionResultDataArray;


				int a = SessionSearch->SearchResults.Num();
				FString s = " num of connections" ;
				if (a == 1) {
					s = s + " is one";
				}
				else {
					s = s + " zero";
				}
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, s);


				//If we have found at least 1 session we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
				if (SessionSearch->SearchResults.Num() > 0)
				{
					
					//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, TEXT("INSIDE"));

					for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
					{
						FSessionResutlData SessionData;
						FOnlineSessionSearchResult result = SessionSearch->SearchResults[SearchIdx];

						FOnlineSessionSettings setting = result.Session.SessionSettings;

						//FString rm;
						/*if (setting.Get(SETTING_SERVER_NAME,rm)) {
							GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, TEXT("settings True"));
						}
						else {
							GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, TEXT("settings false"));
						}*/
						
						//result.Session.SessionSettings.Get(SETTING_SERVER_NAME)
						//result.Session.SessionSettings.Get(SETTING_SERVER_NAME, rm);
						//rm =rm+ "  room name";


						result.Session.SessionSettings.Get(SETTING_SERVER_NAME, SessionData.RoomName);
						GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, SessionData.RoomName);

						SessionData.bIsLAN = result.Session.SessionSettings.bIsLANMatch;
						SessionData.CurrentNumberOfPlayers = result.Session.SessionSettings.NumPublicConnections - result.Session.NumOpenPublicConnections;
						SessionData.MaxNumberOfPlayers = result.Session.SessionSettings.NumPublicConnections;
						SessionData.Ping = result.PingInMs;

						GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, SessionData.RoomName);

						/////////SessionSettings->Settings.Add(SETTING_SERVER_NAME, ExtraSessionSetting);


						//Get Server Name
						result.Session.SessionSettings.Get(SETTING_SERVER_NAME, SessionData.SessionName);

						//get if the server is password protected
						//result.Session.SessionSettings.Get(SETTING_SERVER_IS_PROTECTED, SessionData.bIsPasswordProtected);

						////get if the server is password protected
						//if (SessionData.bIsPasswordProtected) {

						//	result.Session.SessionSettings.Get(SETTING_SERVER_PROTECT_PASSWORD, SessionData.SessionPassword);
						//}

						SessionResultDataArray.Add(SessionData);
						//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("OnFindSessionsComplete  XX2"));
						// Call GameListWidget methot to update UI of game List
					}

				}
				//call UMG to 
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("Call UMG"));
				gameListWB->UpdateUIGameListOnSearchComplete(SessionResultDataArray);
			}
		}
	}

	bool UGameInfoInstance::QuickJoin(int32 a_LocalUserNum, FName a_SessionName, const FOnlineSessionSearchResult & a_SearchResult)
	{
		bool bSucessful = false;

		//Get OnlineSubsystem we want to work with
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub) {
			//Get SessionInterface from OnlineSubsystem
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid()) {
				
				//Set the Handle again
				OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

				//Call the "JoinSession" Function with the passes "SearchResult". The "SessionSearch->SearchResults" can be used to get such a
				//"FOnlineSessionSearchResult" and pass it. Pretty straight forward!
				bSucessful = Sessions->JoinSession(a_LocalUserNum, a_SessionName, a_SearchResult);
			}
			
		}
		return bSucessful;
	}


