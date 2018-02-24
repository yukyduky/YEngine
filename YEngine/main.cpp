#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include <crtdbg.h>
#include "D3D.h"
#include "MemoryManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(519);

	GameManager gm;
	
	MemoryManager* permMemory = new MemoryManager(16, 100);
	Locator::provide(permMemory, MEMORYTYPE::PERM);

	ID3D* d3d = nullptr;
	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(d3d, &D3D(), sizeof(D3D));

	Locator::provide(d3d);

	Locator::getD3D()->initializeWindow(hInstance, true, 800, 600, true);
	Locator::getD3D()->createSwapChain();

	// Initialize the game
	gm.init(hInstance, nCmdShow);

	// Game loop
	while (gm.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
	}

	gm.cleanup();
	d3d->cleanup();
	permMemory->cleanup();
	delete permMemory;

	return 0;
}
