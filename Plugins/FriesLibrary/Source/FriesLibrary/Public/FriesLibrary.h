// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FFriesLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};