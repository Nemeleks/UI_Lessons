#pragma once

#include "Slate.h"

class UI_LESSONS_API FStyleSet
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

private:
	static TSharedPtr<class ISlateStyle> StylePtr;
};