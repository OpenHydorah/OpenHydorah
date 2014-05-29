/**
 * \file filesystem.h
 */

#ifndef OPENHYDORAH_FILESYSTEM_H
#define OPENHYDORAH_FILESYSTEM_H

#include <physfs.h>
#include <stdint.h>

/**
 * \brief Reads entire file and returns the memory buffer
 *
 * \param[in] filename Path to the file to read
 * \param[out] buf The buffer to fill with data
 *
 * \return Amount of bytes read. If 0, then \em buf is invalid
 */
PHYSFS_sint64 fs_read_buffer(const char *filename, uint8_t **buf);

#endif
