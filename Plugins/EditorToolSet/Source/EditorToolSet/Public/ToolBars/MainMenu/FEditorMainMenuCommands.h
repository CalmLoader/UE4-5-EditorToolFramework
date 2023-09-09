// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorToolSetStyle.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorMainMenuCommands : public TCommands<FEditorMainMenuCommands>
{
public:
	FEditorMainMenuCommands()
		: TCommands<FEditorMainMenuCommands>(
			TEXT("EditorMainMenu"), NSLOCTEXT("Contexts", "EditorToolSet", "EditorToolSet Plugin"), NAME_None,
			FEditorToolSetStyle::GetStyleSetName())
	{
	}
	
	virtual ~FEditorMainMenuCommands() override;
	virtual void RegisterCommands() override;
public:
	TSharedPtr<FUICommandInfo> MainMenuShowMessage;
	TSharedPtr<FUICommandInfo> MainMenuOpenWindow;
	TSharedPtr<FUICommandInfo> MainMenuChooseFolder;
};
