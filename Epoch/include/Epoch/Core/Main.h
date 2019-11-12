#pragma once

extern Epoch::Application* Epoch::create_application();

int main(int argc, char** argv)
{
	auto app = Epoch::create_application();
	app->run();
	delete app;
}