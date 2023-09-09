// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FEditorBPMenuController.h"
/**
 * 
 */
class EDITORTOOLSET_API FEditorBPMenuBar 
{
public:
	FEditorBPMenuBar();
	virtual ~FEditorBPMenuBar() = default;
	virtual void Initialize() ;

	void BindController(FEditorBPMenuController* BPMenuController);

	FText ToolName;
	
protected:
	void BuildToolbar(FToolBarBuilder& ToolbarBuilder);
	void BuildMenubar(FMenuBarBuilder& MenuBarBuilder);

private:
	UObject* ContextObject;
	FEditorBPMenuController* EditorBPMenuController;
};
