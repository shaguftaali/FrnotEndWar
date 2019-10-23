// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickMatchMenu.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDWAR_API UQuickMatchMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Setting")
		bool bEnableLAN;

	UFUNCTION(BlueprintCallable)
	void OnQuckiBtnClicked(int32 SessionIndex, bool a_IsLAN, bool a_isPresence);

	
};
