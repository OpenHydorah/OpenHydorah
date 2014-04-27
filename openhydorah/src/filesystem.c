#include "filesystem.h"
#include <SDL.h>

PHYSFS_sint64 ReadFileToBuffer(const char* filename, uint8_t** buf)
{
	PHYSFS_File* file = NULL;
	PHYSFS_sint64 fileLength = 0;

	if (PHYSFS_exists(filename) == 0)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not find file '%s'.",
				filename
				);
		return 0;
	}

	file = PHYSFS_openRead(filename);
	if (file == NULL)
	{
		SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not open file '%s'.",
				filename
				);
		return 0;
	}

	fileLength = PHYSFS_fileLength(file);
	(*buf) = malloc(fileLength);
	PHYSFS_read(file, (*buf), 1, fileLength);
	PHYSFS_close(file);

	return fileLength;
}
