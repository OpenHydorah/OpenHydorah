#ifndef OPENHYDORAH_SPRITE_H
#define OPENHYDORAH_SPRITE_H

#include <SDL.h>
#include <stdint.h>
#include "texture.h"
#include "frame.h"
#include "animation.h"
#include <jansson.h>

typedef struct {
	Texture* texture;
	Frame* frames;
	Animation* animations;
	uint32_t numFrames;
	uint32_t numAnimations;
	Frame* currentFrame;
	Animation* activeAnimation;
} Sprite;

Sprite* CreateSprite(void);

Sprite* CreateSpriteFromJSON(json_t* root, TextureList** textures);

Sprite* GetSprite(const char* filename, TextureList** textures);

void DestroySprite(Sprite* sprite);

void DrawSpriteAtPoint(Sprite* sprite, SDL_Point point, SDL_Renderer* renderer);

#endif // OPENHYDORAH_SPRITE_H
