#include "filesystem.h"
#include <SDL.h>

PHYSFS_sint64 fs_read_buffer(const char *filename, uint8_t **buf)
{
	PHYSFS_File* file = NULL;
	PHYSFS_sint64 file_length = 0;

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

	file_length = PHYSFS_fileLength(file);
	(*buf) = malloc(file_length);
	PHYSFS_read(file, (*buf), 1, file_length);
	PHYSFS_close(file);

	return file_length;
}
