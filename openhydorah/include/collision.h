/**
 * \file collision.h
 */

#ifndef OPENHYDORAH_COLLISION_H
#define OPENHYDORAH_COLLISION_H

#include <stdint.h>
#include <jansson.h>
#include <SDL.h>
#include "vector.h"
#include "list.h"

enum collision_type {
	POLYGON
};

/**
 * \struct collision_object
 *
 * A collision object is a collection
 * of points that together form some
 * geometry that is tested for intersections
 */
struct collision_object {
	struct vec2 *parent;
	struct vec2 *points;
	uint32_t num_points;
	struct vec2 center;
	float area;
	float radius;
	enum collision_type type;
	struct list list;
};

/**
 * \struct collision
 *
 * Contains collision data for a collision
 */
struct collision {
	uint8_t intersects;
	uint8_t will_intersect;
	struct vec2 minimum_translation_vector;
};

/**
 * \brief Creates a collision_object from a JSON object
 *
 * \param[in] root The json object
 * \param[in] parent The parent position
 *
 * \return The new collision_object
 */
struct collision_object *collision_object_create_json(json_t *root,
		struct vec2 *parent);

/**
 * \brief Creates a collision_object list from a JSON array
 *
 * \param[out] list The list to fill
 * \param[in] root The json array
 * \param[in] parent The parent position
 *
 * \return 0 on success, non-zero on error
 */
uint8_t collision_object_list_create_json(struct list *list, json_t *root,
		struct vec2 *parent);

/**
 * \param[in] col_obj The collision_object to destroy
 */
void collision_object_destroy(struct collision_object *col_obj);

/**
 * \brief Draws a collision object
 *
 * \param[in] col_obj The collision_object to draw
 * \param[in] renderer The renderer to use
 */
void collision_object_draw(struct collision_object *col_obj,
		SDL_Renderer *renderer);

/**
 * \param[in] col_obj The collision_object to calculate for
 *
 * \return The area of the collision_object
 */
float collision_object_calc_area(struct collision_object *col_obj);

float collision_object_calc_radius(struct collision_object *col_obj);

/**
 * Requires that the area of the collision_object has been
 * calculated.
 *
 * \param[in] col_obj The collision_object to calculate for
 *
 * \return The center of the collision_object
 */
struct vec2 collision_object_calc_center(struct collision_object *col_obj);

/**
 * \brief Project a collision_object onto an axis, and return the min
 * and maximum points of the collision_object
 *
 * \param[in] col_obj The collision_object to project
 * \param[in] axis The axis to project onto
 * \param[out] min The minimum value on the axis
 * \param[out] max The maximum value on the axis
 */
void collision_object_project(struct collision_object *col_obj, struct vec2 axis,
		float *min, float *max);

struct collision
*collision_check(struct collision_object *obj1, struct collision_object *obj2,
		float rel_x, float rel_y);

struct collision
*collision_list_check(struct list *list, struct collision_object *obj,
		float rel_x, float rel_y);

struct collision
*collision_list_check_list(struct list *list1, struct list *list2,
		float rel_x, float rel_y);

void collision_destroy(struct collision *coll);

uint8_t collision_get_intersects(struct collision *coll);
uint8_t collision_get_will_intersect(struct collision *coll);
float collision_get_mtv_x(struct collision *coll);
float collision_get_mtv_y(struct collision *coll);

#endif
