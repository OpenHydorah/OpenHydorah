#include "init.h"
#include "cleanup.h"
#include "globals.h"

int Initialize(const int width, const int height, char* argv[])
{
	if (InitSDL(&g_window, &g_renderer, width, height) != 0) {
		CleanSDL(g_window, g_renderer);
		return 1;
	}

	if (InitFS(argv[0]) != 0) {
		return 1;
	}

	return 0;
}
