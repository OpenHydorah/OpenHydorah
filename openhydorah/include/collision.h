#ifndef OPENHYDORAH_COLLISION_H
#define OPENHYDORAH_COLLISION_H

#include <SDL.h>
#include <jansson.h>

typedef SDL_Rect CollisionBox;

CollisionBox CreateCollisionBoxFromJSON(json_t* root);

void DrawCollisionBox(CollisionBox box, SDL_Renderer* renderer);

#endif // OPENHYDORAH_COLLISION_H
