#include <SDL.h>
#include "init.h"
#include "cleanup.h"
#include "texture.h"
#include "globals.h"
#include "mod.h"
#include "map.h"
#include "editor.h"

int main(int argc, char* argv[])
{
	if (Initialize(600, 480, argv) != 0)
	{
		return 1;
	}
	SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_ADD);

	ModInfo* info = GetModInfo("mods/libhydorah.so");
	if (info == NULL)
		return 1;

	printf("Found mod:\n\t%s - %s\n", info->name, info->description);

	Mod* mod = CreateMod(info);

	TextureList* textures = NULL;

	Map* map = CreateMapFromFile("maps/test.map", &textures);
	Editor* editor = CreateEditor(map);

	int running = 1;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
			
			HandleEditorEvents(editor, &event);
		}

		SDL_RenderClear(g_renderer);

		DrawMap(map, g_renderer);

		DrawEditor(editor, g_renderer);

		SDL_RenderPresent(g_renderer);
	}

	DestroyMap(map);
	DestroyTextureList(textures);
	DestroyEditor(editor);
	DestroyMod(mod);

	Cleanup(g_window, g_renderer);

	return 0;
}
