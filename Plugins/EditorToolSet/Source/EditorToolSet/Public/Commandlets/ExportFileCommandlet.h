// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "ExportFileCommandlet.generated.h"

/**
 * 
 */
UCLASS()
class EDITORTOOLSET_API UExportFileCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params) override;

private:
	void SaveFile(const FString& ContentStr) const;
};
