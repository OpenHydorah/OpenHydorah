#include "actor.h"
#include <string.h>

Actor* CreateActor(Sprite* sprite)
{
	Actor* actor = malloc(sizeof(Actor));
	actor->sprite = sprite;

	return actor;
}
