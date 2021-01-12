// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay(void) override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 MaxAttempts;
	int32 Attempts;
	bool IsCorrectGuess;
	int32 WordsIndex;
	int32 BullsCount;
	int32 CowsCount;

	void ResetGame(void);
	FString GenerateIsogram(void);
	bool IsValidInput(const FString& Input) const;
	bool IsGameRunning(void) const;
	void CalculateBullsCows(const FString& Input);
};
