// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FEditorMainMenuController.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorMainMenuBar
{
public:
	FEditorMainMenuBar();
	virtual ~FEditorMainMenuBar() = default;
	virtual void Initialize();

	void BindController(FEditorMainMenuController* Controller);

public:
	FText ToolName;
	
protected:
	void BuildMenubar(FMenuBarBuilder& MenuBarBuilder);
	void FillPullDownMenu(FMenuBuilder& MenuBuilder);

private:
	FEditorMainMenuController* EditorMainMenuController;
};
