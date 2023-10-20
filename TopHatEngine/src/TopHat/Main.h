#pragma once

#ifdef TH_PLATFORM_WINDOWS

extern TopHat::Application* TopHat::CreateGame();
int main(int argc, char** argv)
{
	/*TopHat::Log::init();*/
	/*TH_ENGINE_INFO("Engine Initialised");*/
	auto game = TopHat::CreateGame();
	game->Run();
	delete game;
}
#endif // TH_PLATFORM_WINDOWS
