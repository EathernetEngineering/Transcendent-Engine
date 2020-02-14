#include "tepch.h"
#include "Application.h"

int main(int argc, char* argv) {

	auto app = TE::createApplication();

	app->run();

	delete app;

	 return 0;
}