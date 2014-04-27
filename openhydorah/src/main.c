#include <SDL.h>
#include "init.h"
#include "cleanup.h"
#include "sprite.h"
#include "texture.h"
#include "globals.h"
#include "mod.h"

int main(int argc, char* argv[])
{
	if (Initialize(600, 480, argv) != 0)
	{
		return 1;
	}

	ModInfo* info = GetModInfo("mods/libhydorah.so");
	if (info == NULL)
		return 1;

	printf("Found mod:\n\t%s - %s\n", info->name, info->description);

	SDL_Point pos;
	pos.x = 100;
	pos.y = 100;

	TextureList* textures = NULL;

	Sprite* asteroid_big = GetSprite("/sprites/asteroid_big.spr", &textures);

	int running = 1;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
			else if (event.type == SDL_KEYDOWN &&
					event.key.keysym.scancode == SDL_SCANCODE_D)
			{
				Sprite* spr = asteroid_big;
				if (spr->activeAnimation == NULL)
				{
					spr->currentFrame = spr->animations->start;
					spr->activeAnimation = spr->animations;
				}
				else
					spr->activeAnimation = NULL;
			}
		}

		SDL_RenderClear(g_renderer);

		DrawSpriteAtPoint(asteroid_big, pos, g_renderer);
		
		SDL_RenderPresent(g_renderer);
	}


	DestroyTextureList(textures);
	DestroySprite(asteroid_big);

	Cleanup(g_window, g_renderer);

	return 0;
}
