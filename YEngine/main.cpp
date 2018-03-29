#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include <crtdbg.h>
#include "MemoryManager.h"
#include "YEngine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(519);

	GameManager gm;
	
	MemoryManager* permMemory = new MemoryManager(16, 100);
	Locator::provide(permMemory, MEMORYTYPE::PERM);

	YEngine::init(RENDERER::DEFERRED, hInstance, nCmdShow, 800, 600, true);

	// Initialize the game
	gm.init();

	// Game loop
	while (gm.getIsRunning()) 
	{
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
	}

	gm.cleanup();
	permMemory->cleanup();
	delete permMemory;
	YEngine::cleanup();

	return 0;
}
