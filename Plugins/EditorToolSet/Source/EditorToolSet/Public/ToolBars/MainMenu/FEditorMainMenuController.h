// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorMainMenuController
{
public:
	FEditorMainMenuController();
	~FEditorMainMenuController();

	TSharedRef<FUICommandList> GetCommandList();
	void BindCommands();
	void MainMenuShowMessage();
	void MainMenuOpenWindow();
	void MainMenuChooseFolder();
	
protected:
	TSharedRef<FUICommandList> CommandList;

};
