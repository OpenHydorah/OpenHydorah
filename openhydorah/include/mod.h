#ifndef OPENHYDORAH_MOD_H
#define OPENHYDORAH_MOD_H

typedef struct {
	char* name;
	char* description;
	char* filename;
	void* handle;
} ModInfo;

typedef struct {
	ModInfo* info;
} Mod;

ModInfo* GetModInfo(const char* filename);

void DestroyModInfo(ModInfo* info);

Mod* CreateMod(ModInfo* info);

void DestroyMod(Mod* mod);

#endif // OPENHYDORAH_MOD_H
