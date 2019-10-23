// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDWAR_API UMapMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnCreateRoomBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuickMatchBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnGameListBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnAcceptBtnClicked();

	
	
};
