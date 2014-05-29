/**
 * \file animation.h
 */

#ifndef OPENHYDORAH_ANIMATION_H
#define OPENHYDORAH_ANIMATION_H

#include "frame.h"
#include <stdint.h>

struct animation {
	char *name;
	struct frame **frames;
	uint32_t num_frames;
};

/**
 * \param[in] name The name of the animation
 * \param[in] frames The array of frames
 * \param[in] num_frames The number of frames
 *
 * \return The new animation
 */
struct animation *animation_create(const char *name, struct frame **frames,
		uint32_t num_frames);

/**
 * \param[in] root The JSON object
 * \param[in] frames The frames to do look-up from
 * \param[in] num_frames The number of frames
 *
 * \return The new animation
 */
struct animation *animation_create_json(json_t *root, struct frame **frames,
		uint32_t num_frames);

/**
 * \param[in] root The JSON array
 * \param[in] frames The frames to do look-up from
 * \param[in] num_frames The number of frames
 * \param[out] num The number of animations created
 *
 * \return The new array of animations
 */
struct animation **animation_array_create_json(json_t *root, struct frame **frames,
		uint32_t num_frames, uint32_t *num);

/**
 * \param[in] animation The animation to destroy
 */
void animation_destroy(struct animation *animation);

#endif
