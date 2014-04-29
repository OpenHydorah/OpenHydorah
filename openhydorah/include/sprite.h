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
	Frame* currentFrame;
	Animation* activeAnimation;
} Sprite;

Sprite* CreateSprite(Texture* texture, Frame* frames, Frame* defaultFrame, Animation* animations);

Sprite* CreateSpriteFromJSON(json_t* root, TextureList** textures);

Sprite* CreateSpriteFromFile(const char* filename, TextureList** textures);

void DestroySprite(Sprite* sprite);

void DrawSpriteAtPoint(Sprite* sprite, SDL_Point point, SDL_Renderer* renderer);

#endif // OPENHYDORAH_SPRITE_H
