/**
 * \file dictionary.h
 */

#ifndef OPENHYDORAH_DICTIONARY_H
#define OPENHYDORAH_DICTIONARY_H

struct dict {
	char *key;
	struct dict *next;
};

/**
 * \param[in] dict The dictionary to initialize
 * \param[in] key The key associated with the dictionary
 */
void dict_init(struct dict *dict, const char *key);

/**
 * \param[in] new The dictionary to add to head
 * \param[in] head The dictionary to append to
 */
void dict_append(struct dict *new, struct dict *head);

/**
 * \param[in] key The key to search for
 * \param[in] head The dictionary to search through
 *
 * \return The dictionary, associated with key, if found.
 * NULL otherwise.
 */
struct dict *dict_find(const char* key, struct dict *head);

/**
 * \param[in] key The key to search for
 * \param[in] head The dictionary to search through
 *
 * \return The dictionary entry, associated with key, if found.
 * NULL otherwise.
 */
struct dict *dict_find_entry(const char* key, struct dict *head);

#endif
