#pragma once

#include "Transcendent-Engine/core/Application.h"

#ifdef TE_PLATFORM_WINDOWS
int main(int argc, char** argv) {

	TE::Log::Init();

	TE_PROFILE_BEGIN_SESSION("TE::CreateApplication()", "CraeteAppProfileResults.json");
	auto app = TE::createApplication();
	TE_PROFILE_END_SESSION();

	TE_PROFILE_BEGIN_SESSION("app->Run()", "RunLoopProfileResults.json");
	app->Run();
	TE_PROFILE_END_SESSION();

	TE_PROFILE_BEGIN_SESSION("delete app", "AppDeconstructionProfileResults.json");
	delete app;
	TE_PROFILE_END_SESSION();

	return 0;
}
#endif