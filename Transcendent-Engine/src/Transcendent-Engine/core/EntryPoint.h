#pragma once

#include "core.h"

#ifdef TE_PLATFORM_WINDOWS
int main(int argc, char* argv) {

	auto app = TE::createApplication();

	app->run();

	delete app;

	return 0;
}
#endif