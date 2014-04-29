#ifndef OPENHYDORAH_INIT_H
#define OPENHYDORAH_INIT_H

#include <SDL.h>
#include <physfs.h>

int InitSDL(SDL_Window** window, SDL_Renderer** renderer,
		const int width, const int height);

int InitFS(const char* arg0);

int Initialize(const int width, const int height, char* argv[]);

#endif // OPENHYDORAH_INIT_H
