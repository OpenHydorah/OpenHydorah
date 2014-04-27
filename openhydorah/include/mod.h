#ifndef OPENHYDORAH_MOD_H
#define OPENHYDORAH_MOD_H

typedef struct {
	char* name;
	char* description;
} ModInfo;

typedef struct {
	ModInfo* info;
	void* handle;
} Mod;

ModInfo* GetModInfo(const char* filename);

#endif // OPENHYDORAH_MOD_H
