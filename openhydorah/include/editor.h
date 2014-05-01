/** \file editor.h
 * Contains structs and functions for the
 * in-game editor
 */

#ifndef OPENHYDORAH_EDITOR_H
#define OPENHYDORAH_EDITOR_H

#include <SDL.h>
#include "object.h"
#include "map.h"
#include <stdint.h>

/** \struct SEditor
 * \brief Defines the editor
 *
 * \em SEditor contains the collection
 * of data that the editor requires.
 */
typedef struct SEditor {
	uint8_t active;
	Map* map;
	ObjectList* selected;
	SDL_Rect selectionRect;
	SDL_Point selectionStart;
	uint32_t gridWidth;
	uint32_t gridHeight;
	uint8_t showCollisions;
	uint8_t showGrid;
	uint8_t showSelectionBox;
	uint8_t isDragging;
} Editor;

/** \brief Allocates memory for a new Editor
 * and returns the pointer
 *
 * \param[in] map The \em Map to edit
 *
 * \return Pointer to the new Editor
 */
Editor* CreateEditor(Map* map);

/** \brief Set the Editor to draw
 * itself
 *
 * \param[in] editor The Editor to show
 */
void ShowEditor(Editor* editor);

/** \brief Set the Editor stop drawing
 * itself
 *
 * \param[in] editor The Editor to hide
 */
void HideEditor(Editor* editor);

/** \brief Draws the editor
 *
 * \param[in] editor The Editor to draw
 * \param[in] renderer The renderer to use
 */
void DrawEditor(Editor* editor, SDL_Renderer* renderer);

/** \brief Deallocates and cleans the Editor
 *
 * \param[in] editor The editor to destroy
 */
void DestroyEditor(Editor* editor);

/** \brief Draw an indicator of which objects
 * are currently selected
 *
 * \todo Function is not well defined. Change!
 *
 * \param[in] selection The list of objects that are selected
 * \param[in] renderer The renderer to use
 */
void RenderSelection(ObjectList* selection, SDL_Renderer* renderer);

/**
 * \todo Function is not well defined. Change!
 */
void RenderSelectionObjects(Object* obj, SDL_Renderer* renderer);

/** \brief Handle event for editor
 *
 * This should be called in the event loop
 *
 * \param[in] editor The Editor to handle event for
 * \param[in] event The event
 */
void HandleEditorEvents(Editor* editor, SDL_Event* event);

/** \brief Draws the grid for the editor
 *
 * \param[in] editor The editor to draw for
 * \param[in] renderer The renderer to use
 */
void RenderEditorGrid (Editor* editor, SDL_Renderer* renderer);

/** \brief Draws the selection box
 *
 * \param[in] editor The editor to draw for
 * \param[in] renderer The renderer to use
 */
void RenderSelectionBox(Editor* editor, SDL_Renderer* renderer);

#endif // OPENHYDORAH_EDITOR_H
