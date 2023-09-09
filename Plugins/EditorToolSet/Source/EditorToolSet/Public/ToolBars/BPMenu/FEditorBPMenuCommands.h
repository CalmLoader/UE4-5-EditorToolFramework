// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorToolSetStyle.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorBPMenuCommands : public TCommands<FEditorBPMenuCommands>
{
public:
	FEditorBPMenuCommands(): TCommands<FEditorBPMenuCommands>(
		TEXT("EditorBPMenu"), NSLOCTEXT("Contexts", "EditorToolSet", "EditorToolSet Plugin"), NAME_None,
		FEditorToolSetStyle::GetStyleSetName())
	{
	}

	virtual ~FEditorBPMenuCommands() override;

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> BPMenuShowMessage;
	TSharedPtr<FUICommandInfo> BPMenuOpenWindow;
	TSharedPtr<FUICommandInfo> BPMenuChooseFolder;
};
