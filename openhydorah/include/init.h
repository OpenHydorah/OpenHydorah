/** \file init.h
 * Contains functions engine initialization
 */

#ifndef OPENHYDORAH_INIT_H
#define OPENHYDORAH_INIT_H

#include <SDL.h>
#include <physfs.h>

/** \brief Initializes SDL
 *
 * \param[out] window Returns the created window
 * \param[out] renderer Returns the created renderer
 * \param[in] width The window width
 * \param[in] height The window height
 *
 * \return Non zero if there was an error.
 */
int InitSDL(SDL_Window** window, SDL_Renderer** renderer,
		const int width, const int height);

/** \brief Initializes PHYSFS
 *
 * \param[in] arg0 The first argument returned to main's argv.
 * Pass NULL if Windows
 *
 * \return Non zero if there was an error.
 */
int InitFS(const char* arg0);

/** \brief Initializes engine
 *
 * \param[in] width The window width
 * \param[in] height The window height
 * \param[in] argv The main's argv argument
 *
 * \return Non zero if there was an error.
 */
int Initialize(const int width, const int height, char* argv[]);

#endif // OPENHYDORAH_INIT_H
