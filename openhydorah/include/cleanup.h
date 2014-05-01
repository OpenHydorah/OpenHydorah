/** \file cleanup.h
 * Contains structs and functions for
 * deinitilization and cleanup
 */

#ifndef OPENHYDORAH_CLEANUP_H
#define OPENHYDORAH_CLEANUP_H

#include <SDL.h>

/** \brief Clean up SDL, and all its relevant
 * thing
 *
 * \param[in] window The window to destroy
 * \param[in] renderer The renderer to destroy
 */
void CleanSDL(SDL_Window* window, SDL_Renderer* renderer);

/** \brief Clean up the engine
 *
 * \param[in] window The window to destroy
 * \param[in] renderer The renderer to destroy
 */
void Cleanup(SDL_Window* window, SDL_Renderer* renderer);

#endif // OPENHYDORAH_CLEANUP_H
