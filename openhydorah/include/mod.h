/**
 * \file mod.h
 */

#ifndef OPENHYDORAH_MOD_H
#define OPENHYDORAH_MOD_H

#include <stdint.h>

/**
 * \struct mod_info
 * \brief Contains information for a mod
 */
struct mod_info {
	char *name;
	char *description;
	char *filename;
	void *handle;
};

/**
 * \struct mod
 *
 * A mod is external code that
 * acts on specific calls
 * required by the engine
 */
struct mod {
	struct mod_info *info;
	void (*update)(void*, uint32_t);
	void (*init)(void*);
	void (*destroy)(void*);
};

/**
 * \brief Queries a mod for information
 *
 * Calls a function in the mod that is expected
 * to return a specfic amount of information,
 * required to fill mod_info.
 *
 * \param[in] filename Path to the mod
 *
 * \return The new mod_info or NULL on error.
 */
struct mod_info *mod_info_get(const char *filename);

/**
 * \param[in] info The mod_info to destroy
 */
void mod_info_destroy(struct mod_info *info);

/**
 * Creates the mod and informs the mod of initilization
 *
 * \param[in] info The mod's information
 *
 * \return The new Mod
 */
struct mod *mod_create(struct mod_info *info);

/**
 * Destroys the mod, along with the ModInfo.
 * Also informs the mod of exit
 *
 * \param[in] mod The Mod to destroy
 */
void mod_destroy(struct mod *mod);

/**
 * Calls the mod's update function
 *
 * \param[in] mod The mod to update
 * \param[in] dt The delta time since last called
 */
void mod_update(struct mod *mod, uint32_t dt);

#endif
