// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../GameInstance/SessionResultData.h"
#include "GameListWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDWAR_API UGameListWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnSearchBtnClicke(bool bIsLAN);

	UFUNCTION(BlueprintImplementableEvent, Category = "SessionResults")
	void UpdateUIGameListOnSearchComplete(UPARAM(ref)TArray<FSessionResutlData>& SessionResultDataArray);

	/*UFUNCTION(BlueprintImplementableEvent, Category = "SessionResults")
		void XX(UPARAM(ref) TArray<FSessionResutlData>& SessionResultDataArray);

	UFUNCTION(BlueprintImplementableEvent, Category = "SessionResults")
		void AA(int32 ab);
	*/

};
