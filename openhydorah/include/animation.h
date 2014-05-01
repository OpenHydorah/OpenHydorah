/** \file animation.h
 * Contains structs and functions for Animations
 */

#ifndef OPENHYDORAH_ANIMATION_H
#define OPENHYDORAH_ANIMATION_H

#include "frame.h"
#include <jansson.h>

/** \struct SAnimation
 * \brief Defines an animation
 *
 * An Animation is a collection
 * of Frames, that it can iterate
 * through.
 */
typedef struct SAnimation {
	char* name;
	Frame* frames;
	Frame* start;
	struct SAnimation* next;
} Animation;

/** \brief Allocate memory for a new Animation
 * and return it
 *
 * \return Pointer to the new Animation
 */
Animation* CreateAnimation(void);

/** \brief Create an Animation from a JSON object
 *
 * \param[in] root The JSON object
 * \param[in] frames The frames that have been created
 * before, which the Animation will link to.
 *
 * \return Pointer to the new Animation
 */
Animation* CreateAnimationFromJSON(json_t* root, Frame* frames);

/** \brief Create Animations from a JSON array
 *
 * \param[in] root The JSON array
 * \param[in] frames The frames that have been created
 * before, which the Animation will link to.
 *
 * \return Pointer to the new Animation
 */
Animation* CreateAnimationsFromJSON(json_t* root, Frame* frames);

#endif // OPENHYDORAH_ANIMATION_H
