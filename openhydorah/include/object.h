/** \file object.h
 * Contains structs and functions for Objects
 */

#ifndef OPENHYDORAH_OBJECT_H
#define OPENHYDORAH_OBJECT_H

#include "sprite.h"
#include <SDL.h>
#include <jansson.h>
#include "collision.h"

/** \struct SObject
 * \brief Defines a game object
 *
 * An Object is a game object that has a
 * sprite, collision data and a location in the game.
 * 
 * Objects are organized in a hierarchy, so that any
 * object can have a number of children and siblings.
 *
 * For example, an enemy in the game could consist of
 * a root Object that is the body, and two child objects
 * that are its weapons.
 *
 * Each of the objects should be able to move independently,
 * but child objects inherit transformation data from their
 * parents.
 */
typedef struct SObject {
	Sprite* sprite;
	char* name;
	SDL_Point point;
	CollisionBox collision;
	struct SObject* children;
	struct SObject* parent;
	struct SObject* next;
} Object;

/** \struct SObjectList
 * \brief Represents a list of Objects
 *
 * An ObjectList is useful for seperating
 * Objects from their hierarchy nature,
 * by collecting them in a linear fashion.
 */
typedef struct SObjectList {
	Object* object;
	struct SObjectList* next;
} ObjectList;

/** \brief Allocates memory for a new Object
 * and returns the pointer
 *
 * \param[in] sprite The object's sprite
 * \param[in] name The object's name.
 * Pass NULL if you don't intend to search for it
 * \param[in] point The object's position
 * \param[in] collision The object's collision box
 * \param[in] parent The object's parent
 * \param[in] children The object's children
 *
 * \returns Pointer to the new Object. NULL if error.
 */
Object* CreateObject(Sprite* sprite, const char* name,
		SDL_Point point, CollisionBox collision, Object* parent,
		Object* children);

/** \brief Creates an object from a JSON object
 *
 * \param[in] root The JSON object
 * \param[in] point The object's position
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The object's parent
 *
 * \return Pointer to the new Object
 */
Object* CreateObjectFromJSON(json_t* root, SDL_Point point,
		TextureList** textures, Object* parent);

/** \brief Creates a object hierarchy from a JSON array
 *
 * \param[in] root The JSON array
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The object's parent
 *
 * \return Pointer to the new Object
 */
Object* CreateObjectsFromJSON(json_t* root, TextureList** textures,
		Object* parent);

/** \brief Creates an object from a file
 *
 * \param[in] filename Path to the file to read
 * \param[in] point The object's position
 * \param[out] textures The list to add the sprite's texture to
 * \param[in] parent The object's parent
 *
 * \return Pointer to the new Object
 */
Object* CreateObjectFromFile(const char* filename, SDL_Point point,
		TextureList** textures, Object* parent);

/** \brief Draws the Object 
 *
 * \param[in] object The object to draw
 * \param[in] renderer The renderer to use
 */
void DrawObject(Object* object, SDL_Renderer* renderer);

/** \brief Draws the Object's collision box
 *
 * \warning This function will most likely be replaced
 * with a generic collision draw function
 *
 * \param[in] object The object's collision box to draw
 * \param[in] renderer The renderer to use
 */
void DrawObjectCollisions(Object* object, SDL_Renderer* renderer);

/** \brief Deallocates and cleans an Object
 *
 * Destroys the object and its children.
 * Not its siblings.
 *
 * \param[in] object The object to destroy
 */
void DestroyObject(Object* object);

/** \brief Deallocates and cleans the list
 *
 * Destroys the list, but not the objects.
 *
 * \param[in] list The list to destroy
 */
void DestroyObjectList(ObjectList* list);

/** \brief Adds a child to an object
 *
 * It adds the child unmodified, so its hierarchy
 * is added as well.
 *
 * \param[in] parent The Object to add to
 * \param[in] child The Object to add
 */
void AddChildObject(Object* parent, Object* child);

/** \brief Finds one object in point
 *
 * \warning Does not handle overlapping objects properly.
 * \todo Change to use ObjectList
 *
 * \param[in] root The Object hierarchy to search through
 * \param[in] point The point to check for
 *
 * \return The first object that contains the \em point.
 * NULL if not found.
 */
Object* FindObjectInPoint(Object* root, SDL_Point point);

/** \brief Finds first object with name
 *
 * \warning Only returns the first Object with name
 * \todo Change to use ObjectList
 *
 * \param[in] root The Object hierarchy to search through
 * \param[in] name The name to search for
 *
 * \return The first Object with \em name. NULL if not found.
 */
Object* FindObjectByName(Object* root, const char* name);

/** \brief Finds objects in that collide with rectangle
 *
 * \param[in] root The Object hierarchy to search through
 * \param[in] rect The rectangle to check for
 *
 * \return List of objects that collided with \em rect.
 * NULL if not found.
 */
ObjectList* FindObjectsInRect(Object* root, SDL_Rect rect);

#endif // OPENHYDORAH_OBJECT_H
