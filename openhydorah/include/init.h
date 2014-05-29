/**
 * \file init.h
 * Contains functions for engine initialization
 */

#ifndef OPENHYDORAH_INIT_H
#define OPENHYDORAH_INIT_H

#include <SDL.h>
#include <physfs.h>

/**
 * \brief Initializes SDL
 *
 * \param[out] window Returns the created window
 * \param[out] renderer Returns the created renderer
 * \param[in] width The window width
 * \param[in] height The window height
 *
 * \return Non zero if there was an error.
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer,
		const int width, const int height);

/**
 * \brief Initializes PHYSFS
 *
 * \param[in] arg0 The first argument returned to main's argv.
 * Pass NULL if Windows
 *
 * \return Non zero if there was an error.
 */
int init_fs(const char *arg0);

#endif
