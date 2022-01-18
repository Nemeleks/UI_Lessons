// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowEditorToolCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWindowEditorToolModule"

void FStandaloneWindowEditorToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneWindowEditorTool", "Bring up StandaloneWindowEditorTool window", EUserInterfaceActionType::Button, FInputChord() /*FInputGesture() Depricated*/);
}

#undef LOCTEXT_NAMESPACE
