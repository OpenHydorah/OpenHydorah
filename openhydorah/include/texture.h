/** \file texture.h
 * Contains relevant structs and functions for textures
 */

#ifndef OPENHYDORAH_TEXTURE_H
#define OPENHYDORAH_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

/** \struct Texture
 * \brief Defines a texture
 *
 * A texture should represent visual data,
 * either from a file, or memory data.
 */
typedef SDL_Texture Texture;

/** \struct STextureList
 * \brief Defines a list of textures
 *
 * The list takes ownership of the texture,
 * and destroys them when it is destroyed.
 *
 * typedef as TextureList
 */
typedef struct STextureList {
	Texture* texture;
	char* name;
	struct STextureList* next;
} TextureList;

/** \brief Allocates memory for a TextureList,
 * and returns the pointer
 *
 * \return Pointer to the new TextureList
 */
TextureList* CreateTextureList(void);

/** \brief Adds a texture to the provided list
 *
 * \param[out] list The list to add the texture to
 * \param[in] name The name to associate the texture with
 * \param[in] texture The texture to add
 */
void AddTextureToList(TextureList** list, const char* name, Texture* texture);

/** \brief Get a texture from the provided list
 *
 * \param[in] list The list to search through
 * \param[in] name The name that was associated with the texture
 * \return A pointer to the texture, or NULL if it was not found
 */
Texture* GetTextureFromList(TextureList* list, const char* name);

/** \brief Creates a new texture using data from the specified file
 *
 * \param[in] filename The path to the file to read from
 * \return The new texture, or NULL if there was an error
 */
Texture* CreateTextureFromFile(const char* filename);

/** \brief Deallocate and cleanup a texture
 *
 * \param[in] texture The texture to destroy
 */
void DestroyTexture(Texture* texture);

/** \brief Deallocate and cleanup a list of textures
 *
 * Note that this destroys all textures in the list
 *
 * \param[in] list The list to destroy
 */
void DestroyTextureList(TextureList* list);

#endif // OPENHYDORAH_TEXTURE_H
