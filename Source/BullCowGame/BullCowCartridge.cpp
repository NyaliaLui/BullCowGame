// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "WordsList.h"

void UBullCowCartridge::BeginPlay(void) // When the game starts
{
    Super::BeginPlay();

    //WordsIndex is only set once
    this->WordsIndex = -1;

    //Print welcome message
    this->ResetGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (this->IsGameRunning()) {
        //Check that the input is valid
        //User loses if their guess is incorrect
        //Otherwise User wins.
        if (this->IsValidInput(Input) && (Input == this->HiddenWord)) {
            PrintLine(TEXT("Correct!"));
            this->IsCorrectGuess = true;
        } else {
            ++this->Attempts;
            PrintLine(FString::Printf(TEXT("Incorrect (%i/%i)."), this->Attempts, this->MaxAttempts));
        }   
    } else { //do the negative condition as else branch for compilation optimzations
        this->ResetGame();
    }
}

void UBullCowCartridge::ResetGame(void)
{
    //Generate the hidden isogram and set other member variable
    //defaults
    ++this->WordsIndex;
    this->HiddenWord = this->GenerateIsogram();
    this->MaxAttempts = this->HiddenWord.Len();
    this->Attempts = 0;
    this->IsCorrectGuess = false;

    PrintLine(TEXT("Welcome to the Bulls Cows game!\n"));
    PrintLine(FString::Printf(TEXT("Try to guess an isogram of length %i."), this->HiddenWord.Len()));
}

FString UBullCowCartridge::GenerateIsogram(void)
{
    return Words[this->WordsIndex];
}

bool UBullCowCartridge::IsValidInput(const FString& Input) const
{
    bool ret = true;

    for (int32 i = 0; i < Input.Len()-1; ++i) {

        for (int32 j = i + 1; j < Input.Len()-1; ++j) {
            if (Input[i] == Input[j]) {
                ret = false;
                break;
            }
        }

        if (!ret) {
            break;
        }
    }

    return (ret && (Input.Len() == this->HiddenWord.Len()));
}

bool UBullCowCartridge::IsGameRunning(void) const
{
    return !((this->Attempts >= this->MaxAttempts) || this->IsCorrectGuess);
}

void UBullCowCartridge::CalculateBullsCows(const FString& Input)
{
    for (int32 i = 0; i < Input.Len(); ++i) {
        if (Input[i] == this->HiddenWord[i]) {
            ++this->BullsCount;
            continue;
        }

        for (int32 j = 0; j < this->HiddenWord.Len(); ++j) {
            if (Input[i] == this->HiddenWord[j]) {
                ++this->CowsCount;
                break;
            }
        }
    }
}