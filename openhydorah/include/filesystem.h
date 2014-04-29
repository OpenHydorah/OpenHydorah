#ifndef OPENHYDORAH_FILESYSTEM_H
#define OPENHYDORAH_FILESYSTEM_H

#include <physfs.h>
#include <stdint.h>

PHYSFS_sint64 ReadFileToBuffer(const char* filename, uint8_t** buf);

#endif // OPENHYDORAH_FILESYSTEM_H
