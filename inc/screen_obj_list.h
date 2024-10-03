/**
 * @file screen_obj_list.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __SCREEN_OBJ_LIST_H__
#define __SCREEN_OBJ_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdbool.h>
#include <stddef.h>
#include "screen_object.h"

//---------------------------------- MACROS -----------------------------------
#define MAX_OBJECTS_ON_SCREEN (5)

//-------------------------------- DATA TYPES ---------------------------------
typedef struct
{
    screen_object_t *elems[MAX_OBJECTS_ON_SCREEN];
    size_t           size;
} screen_obj_list_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief List intializer
 *
 */
void screen_obj_list_init(screen_obj_list_t *self);

/**
 * @brief Add element to list
 *
 * @param elem Element to be added
 * @return true Element successfully added
 * @return false List full
 */
bool screen_obj_list_add(screen_obj_list_t *self, screen_object_t *elem);

/**
 * @brief Finds element and deletes it
 *
 * @param elem Element to be removed
 */
void screen_obj_list_erase(screen_obj_list_t *self, screen_object_t *elem);

/**
 * @brief Returns number of elements
 *
 * @return size_t Number of elements
 */
size_t screen_obj_list_size(screen_obj_list_t *self);

/**
 * @brief Returns element on position index or NULL when out of range
 *
 * @param index Position of desired element
 * @return int* Desired element or NULL when out of range
 */
screen_object_t *screen_obj_list_get(screen_obj_list_t *self, size_t index);

/**
 * @brief Deletes all elements
 */
void screen_obj_list_clear(screen_obj_list_t *self);

/**
 * @brief List destructor
 */
void screen_obj_list_destroy(screen_obj_list_t *self);

#ifdef __cplusplus
}
#endif

#endif // __SCREEN_OBJ_LIST_H__
