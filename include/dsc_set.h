// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_SET_H  
#define DSC_SET_H

#include "dsc_data.h"
#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_SET_INITIAL_CAPACITY 16 

#define DSC_SET_LOAD_FACTOR 0.75

typedef struct DSCSet DSCSet;

/**
 * @brief Initialize a new set.
 *
 * @param new_set Pointer to the set to initialize.
 * @param type The data type stored in the set.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_init(DSCSet *new_set, DSCType type);

/**
 * @brief Deinitialize a set, freeing all allocated memory.
 *
 * @param set Pointer to the set to deinitialize.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_deinit(DSCSet *set);

/**
 * @brief Get the current size of the set.
 *
 * @param set Pointer to the set.
 * @param result Pointer to store the size.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_size(const DSCSet *set, size_t *result);

/**
 * @brief Get the current capacity of the set.
 *
 * @param set Pointer to the set.
 * @param result Pointer to store the capacity.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_capacity(const DSCSet *set, size_t *result);

/**
 * @brief Get the current load factor of the set.
 *
 * @param set Pointer to the set.
 * @param load_factor Pointer to store the load factor.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_load_factor(const DSCSet *set, double *load_factor);

/**
 * @brief Check if the set is empty.
 *
 * @param set Pointer to the set.
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_empty(const DSCSet *set, bool *result);

/**
 * @brief Check if the set contains the specified key.
 *
 * @param set Pointer to the set.
 * @param key Pointer to the key data.
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_contains(const DSCSet *set, void *key, bool *result);

/**
 * @brief Insert a key into the set.
 *
 * @param set Pointer to the set.
 * @param key Pointer to the key data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_insert(DSCSet *set, void *key);

/**
 * @brief Erase the specified key from the set.
 *
 * @param set Pointer to the set.
 * @param key Pointer to the key data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_erase(DSCSet *set, void *key);

/**
 * @brief Clear all entries from the set.
 *
 * @param set Pointer to the set.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_set_clear(DSCSet *set);

#endif // DSC_SET_H
