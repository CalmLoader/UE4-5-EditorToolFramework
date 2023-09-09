// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EDITORTOOLSET_API FEditorCommandBase
{
public:
	FEditorCommandBase();
	virtual ~FEditorCommandBase();

	FString CommandName;
	FString HelpContent;
	
	virtual void Execute(const TArray<FString>& Args);
};
