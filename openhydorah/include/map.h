/** \file map.h
 * Contains structs and functions for maps
 */

#ifndef OPENHYDORAH_MAP_H
#define OPENHYDORAH_MAP_H

#include "object.h"
#include "texture.h"

/** \struct SMap
 * \brief Defines a map
 *
 * A map is a scenario in which players play.
 * It contains, for example, static objects, sprites,
 * the player and the enemies.
 */
typedef struct SMap {
	Object* objects;
} Map;

/** \brief Allocates memory for a new Map
 * and returns the pointer
 *
 * \param[in] objects Map's objects
 *
 * \return Pointer to the new Map
 */
Map* CreateMap(Object* objects);

/** \brief Creates a new Map from a JSON object
 *
 * \param[in] root The JSON object
 * \param[out] textures The list to add the sprites' textures
 *
 * \return Pointer to new Map
 */
Map* CreateMapFromJSON(json_t* root, TextureList** textures);

/** \brief Creates a new Map from file
 *
 * \param[in] filename Path to file to read
 * \param[out] textures The list to add the sprites' textures
 *
 * \return Pointer to new Map
 */
Map* CreateMapFromFile(const char* filename, TextureList** textures);

/** \brief Deallocates and cleans Map
 *
 * Destroys the map and its objects
 *
 * \param[in] map The Map to destroy
 */
void DestroyMap(Map* map);

/** \brief Draws the map
 *
 * This draws everything in the Map that
 * can be drawn
 *
 * \param[in] map The Map to draw
 * \param[in] renderer The renderer to use
 */
void DrawMap(Map* map, SDL_Renderer* renderer);

#endif // OPENHYDORAH_MAP_H
