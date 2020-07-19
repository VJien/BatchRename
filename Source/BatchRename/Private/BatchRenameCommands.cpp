// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatchRenameCommands.h"

#define LOCTEXT_NAMESPACE "FBatchRenameModule"

void FBatchRenameCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "BatchRename", "Bring up BatchRename window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
