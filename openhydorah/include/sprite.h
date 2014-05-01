/** \file sprite.h
 * Contains relevant structs and functions for sprites
 */

#ifndef OPENHYDORAH_SPRITE_H
#define OPENHYDORAH_SPRITE_H

#include <SDL.h>
#include <stdint.h>
#include "texture.h"
#include "frame.h"
#include "animation.h"
#include <jansson.h>

/** \struct SSprite
 * \brief Defines a sprite
 *
 * A sprite is a texture with a number
 * of frames and animations.
 */
typedef struct SSprite {
	Texture* texture;
	Frame* frames;
	Animation* animations;
	Frame* currentFrame;
	Animation* activeAnimation;
} Sprite;

/** \brief Allocates memory for a Sprite,
 * and returns the pointer
 *
 * \param[in] texture The sprite's texture
 * \param[in] frames The sprite's frames
 * \param[in] defaultFrame The frame to use by default.
 * If NULL, then it's the first in \em frames
 * \param[in] animations The sprite's animations
 *
 * \return Pointer to the new Sprite. NULL if error.
 */
Sprite* CreateSprite(Texture* texture, Frame* frames, Frame* defaultFrame, Animation* animations);

/** \brief Creates a sprite from a JSON object
 *
 * \params[in] root The JSON object
 * \params[out] textures The list to add the sprite textures to
 * \return Pointer to the new Sprite
 */
Sprite* CreateSpriteFromJSON(json_t* root, TextureList** textures);

/** \brief Creates a sprite from a file
 *
 * \params[in] filename The file to read from
 * \params[out] textures The list to add the sprite textures to
 * \return Pointer to the new Sprite
 */
Sprite* CreateSpriteFromFile(const char* filename, TextureList** textures);

/** \brief Deallocates and cleans up a Sprite
 *
 * \param[in] sprite The sprite to destroy
 */
void DestroySprite(Sprite* sprite);

/** \brief Draws the sprite at the specified point
 *
 * \param[in] sprite Sprite to draw
 * \param[in] point The point to draw at
 * \param[in] renderer The renderer to use
 */
void DrawSpriteAtPoint(Sprite* sprite, SDL_Point point, SDL_Renderer* renderer);

#endif // OPENHYDORAH_SPRITE_H
