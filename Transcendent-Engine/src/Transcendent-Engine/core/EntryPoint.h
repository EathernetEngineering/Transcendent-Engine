#pragma once

#include "Transcendent-Engine/core/Application.h"

#ifdef TE_PLATFORM_WINDOWS
int main(int argc, char** argv) {

	TE::Log::Init();

	auto app = TE::createApplication();

	app->Run();

	delete app;

	return 0;
}
#endif