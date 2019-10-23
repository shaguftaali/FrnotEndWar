// Fill out your copyright notice in the Description page of Project Settings.

//https://wiki.unrealengine.com/How_To_Use_Sessions_In_C++#Joining_a_Session

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../DataSave/PlayerSaveGame.h"
#include "../UI/CreateProfileWidget.h"
#include "Blueprint/UserWidget.h"
#include "../UI/MapMenuWidget.h"
#include "../UI/CreateRoomWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "../UI/QuickMatchMenu.h"
#include "../UI/GameListWidget.h"
#include "SessionResultData.h"
#include "GameInfoInstance.generated.h"


#define SETTING_SERVER_NAME FName(TEXT("SERVERNAMEKEY"))
//#define SETTING_SERVER_IS_PROTECTED FName(TEXT("SERVERSERVERISPASSWORDPROTECTEDKEY"))
//#define SETTING_SERVER_PROTECT_PASSWORD FName(TEXT("SERVERPROTECTPASSWORDKEY"))



/**
 * 
 */


//USTRUCT(BlueprintType)
//struct FSessionResutlData {
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	FString RoomName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	FString MapName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	int32 CurrentNumberOfPlayers;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	int32 MaxNumberOfPlayers;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	FString SessionName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	GameMode ModeOfGame;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	bool bIsLAN;
//
//
//	//====================================
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	bool bIsPasswordProtected;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	FString SessionPassword;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionData")
//	int32 Ping;
//
//};

UCLASS()
class FRONTENDWAR_API UGameInfoInstance : public UGameInstance
{
	GENERATED_BODY()

	

public:
	bool IsCreatedSaveFile ;


public:

	UFUNCTION(BlueprintCallable)
	void InitiateSetUp();

	UFUNCTION(BlueprintCallable)
	void CheckForSavedGame();

	void ShowCreateProfileMenu();

	void ShowMapMenu();

	void ShowCreateRoomMenu();

	void ShowLoadingScreen();

	void ShowQuickMatchMenu();

	void ShowGameListMenu();

	void SaveGameData(UPlayerSaveGame* a_gameData);

	void LaunchLobby(FString ServerName, bool EnableLan );

	UPlayerSaveGame* LoadGameData();


	void StartOnlineGame(FString a_ServerName, bool m_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString a_SessionPassword);

	void FindOnlineGames(bool m_IsLAN, bool a_isPresence);

	void JoinOnlineGame(int32 SessionIndex, bool a_IsLAN, bool a_isPresence);


	//Function fired when a session create request has completed
	virtual void OnCreateSessionComplete(FName a_SesseionName, bool a_WasSuccessful);

	//Function Fired when a session start request has completed
	void OnStartOnlineGameComplete(FName a_SessionName, bool a_WasSuccessful);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FName LobbyMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UCreateProfileWidget> CreateProfileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UMapMenuWidget> MapMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UCreateRoomWidget> CreateRoomClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UQuickMatchMenu> QuickMatchClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UGameListWidget> GameListClass;


		/*UCreateProfileWidget* createProfileWB;

		UMapMenuWidget* mapMenuWB;

		UCreateRoomWidget* createRoomWB;

		UQuickMatchMenu* quickMatchWB;*/
		
	UGameListWidget* gameListWB;



private:

	void BindDelegates();

	//Function to host a game
	bool HostSession(TSharedPtr<const FUniqueNetId> m_userID, FName a_SessionName, FString a_ServerName, bool m_IsLAN, bool a_isPresence, bool bIsPasswordProtected, int32 a_maxNumPlayers, FString SessionPassword);

	//Joins a session via a search result
	bool JoinSession(TSharedPtr<const FUniqueNetId> a_UserID, FName a_SessionName, const FOnlineSessionSearchResult& a_SearchResult);
	//bool JoinSession(TSharedPtr<const FUniqueNetId> a_UserID, FName a_SessionName, const FOnlineSessionSearchResult& a_SearchResult);

	//Delegate fired when a session join request has completed
	void OnJoinSessionComplete(FName a_SessionName, EOnJoinSessionCompleteResult::Type a_Result);

	/*Searching And Findinf a Session*/

	/*Find an online session*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence);

	/* Delegate fired when a session search query has completed*/
	void OnFindSessionsComplete(bool bWasSuccessful);


	bool QuickJoin(int32 a_LocalUserNum, FName a_SessionName, const FOnlineSessionSearchResult& a_SearchResult);



private:

	int32 MaxPlayersInSession;


	FName MainMenuMap;

	APlayerController* playerController;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	
	//Delegate called when session created
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	//Delegate called when session started 
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	//Handles to registered delegates for creating/starting a session
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	
	//Join Session Delegates

	//Delegate for joining a session
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	//Handle to registered delegate for joining a session
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;


	/*Delegates for searching for sessions*/
	FOnFindSessionsCompleteDelegate OnFindSessionCompleteDelegate;

	/* Handle to registered delegate for searching a session*/
	FDelegateHandle OnFindSessionCompleteDelegateHandle;

	/*A varible for our Search settings which will also contain our SearchResults, once this search is complete and successful*/
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;


};
