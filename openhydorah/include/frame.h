/** \file frame.h
 * Contains structs and functions for frames
 */

#ifndef OPENHYDORAH_FRAME_H
#define OPENHYDORAH_FRAME_H

#include <SDL.h>
#include <jansson.h>

/** \struct SFrame
 * \brief Defines a frame
 *
 * A frame is a rectangle
 * in a texture.
 */
typedef struct SFrame {
	char* name;
	SDL_Rect rect;
	struct SFrame* next;
} Frame;

/** \brief Allocates memory for a new Frame
 * and returns the pointer
 *
 * \return Pointer to new Frame
 */
Frame* CreateFrame(void);

/** \brief Create a new from a JSON object
 *
 * \param[in] root The JSON object
 *
 * \return Pointer to new Frame
 */
Frame* CreateFrameFromJSON(json_t* root);

/** \brief Create frames from a JSON array
 *
 * \param[in] root The JSON array
 *
 * \return Pointer to new Frame
 */
Frame* CreateFramesFromJSON(json_t* root);

/** \brief Find a frame with name
 *
 * \param[in] frames The list of frames to search through
 * \param[in] name The name to search for
 *
 * \return Pointer to the frame. NULL if not found.
 */
Frame* FindFrameByName(Frame* frames, const char* name);

#endif // OPENHYDORAH_FRAME_H
