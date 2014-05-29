/**
 * \file list.h
 *
 * This has been heavily inspired by
 * http://kernelnewbies.org/FAQ/LinkedLists
 * and
 * http://www.makelinux.net/ldd3/chp-11-sect-5
 */

#ifndef OPENHYDORAH_LIST_H
#define OPENHYDORAH_LIST_H

struct list {
	struct list *prev;
	struct list *next;
};

/**
 * \param[in] list The list to initialize
 *
 */
void list_init(struct list *list);

/**
 * \param[in] new The list to add to head
 * \param[in] head The list to append to
 *
 */
void list_append(struct list *new, struct list *head);

/**
 * \brief Links the prev and next of the list together
 *
 * \param[in] list The list to remove
 */
void list_remove(struct list *list);

/**
 * \brief Iterate over a list
 *
 * \param[in] iter The &struct list iterator
 * \param[in] head The list to iterate
 */
#define list_for_each(iter, head) \
	for (iter = (head)->next; iter != (head); iter = iter->next)

/**
 * \brief Iterate over a list safely, so that entries can be removed
 *
 * \param[in] iter The &struct list iterator
 * \param[in] n The &struct list variable to use for temporary storage
 * \param[in] head The list to iterate
 */
#define list_for_each_safe(iter, n, head) \
	for (iter = (head)->next, n = iter->next; iter != (head); \
			iter = n, n = iter->next)

/**
 * \brief Get the struct for this entry
 *
 * \param[in] ptr The &struct list iterator
 * \param[in] type The type of the entry
 * \param[in] member The name of the list member of the entry
 *
 * \return Pointer to the entry
 */
#define list_entry(ptr, type, member) ({ \
		const typeof(((type *) 0)->member) *__mptr = (ptr); \
		(type *)((char *)__mptr - ((size_t) &((type *) 0)->member)); })

/**
 * \brief Iterate over the entries of a list
 *
 * \param[in] iter The iterator as a type * of the entries
 * \param[in] head The list to iterate over
 * \param[in] member The name of the list member of the entry
 *
 */
#define list_for_each_entry(iter, head, member) \
	for (iter = list_entry((head)->next, typeof(*iter), member); \
			&iter->member != (head); \
			iter = list_entry(iter->member.next, typeof(*iter), member))

/**
 * \brief Iterate over the entries of a list safely, so that entries
 * can be removed
 *
 * \param[in] iter The iterator as a type * of the entries
 * \param[in] n The type * variable to use for temporary storage
 * \param[in] head The list to iterate
 * \param[in] member The name of the list member of the entry
 */
#define list_for_each_entry_safe(iter, n, head, member) \
	for (iter = list_entry((head)->next, typeof(*iter), member), \
			n = list_entry(iter->member.next, typeof(*iter), member); \
			&iter->member != (head); \
			iter = n, n = list_entry(iter->member.next, typeof(*iter), member)) \

#endif
