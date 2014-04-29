#ifndef OPENHYDORAH_TEXTURE_H
#define OPENHYDORAH_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

typedef SDL_Texture Texture;

typedef struct STextureList {
	Texture* texture;
	char* name;
	struct STextureList* next;
} TextureList;

TextureList* CreateTextureList(void);

void AddTextureToList(TextureList** list, const char* name, Texture* texture);

Texture* GetTextureFromList(TextureList* list, const char* name);

Texture* CreateTextureFromFile(const char* filename);

void DestroyTexture(Texture* texture);

void DestroyTextureList(TextureList* list);

#endif // OPENHYDORAH_TEXTURE_H
