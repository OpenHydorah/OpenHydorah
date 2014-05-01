/** \file mod.h
 * Contains structs and functions for mods
 */

#ifndef OPENHYDORAH_MOD_H
#define OPENHYDORAH_MOD_H

/** \struct SModInfo
 * \brief Contains information for a mod
 */
typedef struct SModInfo {
	char* name;
	char* description;
	char* filename;
	void* handle;
} ModInfo;

/** \struct SMod
 * \brief Defines a mod
 *
 * A mod is external code that
 * acts on and responds to specific calls
 * required by the engine
 */
typedef struct SMod {
	ModInfo* info;
} Mod;

/** \brief Queries a mod for information
 *
 * Calls a function in the mod that is expected
 * to return a specfic amount of information,
 * required to fill ModInfo.
 *
 * \param[in] filename Path to the mod
 *
 * \return Pointer to a new ModInfo. NULL if error.
 */
ModInfo* GetModInfo(const char* filename);

/** \brief Deallocates and cleans a ModInfo
 *
 * \param[in] info The ModInfo to destroy
 */
void DestroyModInfo(ModInfo* info);

/** \brief Allocates memory for a new Mod
 * and returns the pointer
 *
 * Creates the mod and informs the
 * mod of init
 *
 * \param[in] info The Mod's information
 * 
 * \return Pointer to the new Mod
 */
Mod* CreateMod(ModInfo* info);

/** \brief Deallocates and cleans a Mod
 *
 * Destroys the mod, along with the ModInfo.
 * Also informs the mod of exit
 *
 * \param[in] mod The Mod to destroy
 */
void DestroyMod(Mod* mod);

#endif // OPENHYDORAH_MOD_H
