// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FEditorCommandBase.h"

/**
 * 
 */
class EDITORTOOLSET_API FOpenConsoleCommand
{
public:
	FOpenConsoleCommand();
	~FOpenConsoleCommand();

	void RegisterAllConsoleCommands();
	void UnRegisterAllConsoleCommands();

private:
	TArray<FEditorCommandBase*> EditorCommands;
	TArray<IConsoleCommand*> ConsoleCommands;
};
