// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorConsoleCommands/FEditorCommandBase.h"

/**
 * 
 */
class EDITORTOOLSET_API FShowMessageCommand :public FEditorCommandBase
{
public:
	FShowMessageCommand();
	virtual ~FShowMessageCommand() override;

	virtual void Execute(const TArray<FString>& Args) override;
};
