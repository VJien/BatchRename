// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BatchRenameStyle.h"

class FBatchRenameCommands : public TCommands<FBatchRenameCommands>
{
public:

	FBatchRenameCommands()
		: TCommands<FBatchRenameCommands>(TEXT("BatchRename"), NSLOCTEXT("Contexts", "BatchRename", "BatchRename Plugin"), NAME_None, FBatchRenameStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};