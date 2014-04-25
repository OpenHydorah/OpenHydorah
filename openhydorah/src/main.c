/*
This file is part of OpenHydorah.

OpenHydorah is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenHydorah is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenHydorah.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SDL.h>
#include "init.h"
#include "cleanup.h"
#include "sprite.h"
#include "texture.h"
#include "refptr.h"
#include "globals.h"
#include "dictionary.h"

int main(int argc, char* argv[])
{
	if (Initialize(600, 480, argv) != 0)
	{
		return 1;
	}

	TextureList* textures = NULL;

	RefPtr asteroid_big = GetSprite("/sprites/asteroid_big.spr", &textures);

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
				Sprite* spr = asteroid_big->ptr;
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

		DrawSprite(asteroid_big, g_renderer);
		
		SDL_RenderPresent(g_renderer);
	}

	DestroyRefPtr(&asteroid_big);

	DestroyTextureList(textures);

	Cleanup(g_window, g_renderer);

	return 0;
}
