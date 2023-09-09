// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorToolSetStyle.h"

class FEditorToolSetCommands : public TCommands<FEditorToolSetCommands>
{
public:

	FEditorToolSetCommands()
		: TCommands<FEditorToolSetCommands>(TEXT("EditorToolSet"), NSLOCTEXT("Contexts", "EditorToolSet", "EditorToolSet Plugin"), NAME_None, FEditorToolSetStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > DoSomething01;
	TSharedPtr< FUICommandInfo > DoSomething02;
};
