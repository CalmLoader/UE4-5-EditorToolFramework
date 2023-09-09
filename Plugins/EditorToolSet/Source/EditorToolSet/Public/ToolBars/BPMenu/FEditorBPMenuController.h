// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorBPMenuController
{
public:
	FEditorBPMenuController();
	~FEditorBPMenuController();

	TSharedRef<FUICommandList> GetCommandList();
	void BindCommands();

	void BPMenuShowMessage();
	void BPMenuOpenWindow();
	void BPMenuChooseFolder();
	
protected:
	TSharedRef<FUICommandList> CommandList;
};
