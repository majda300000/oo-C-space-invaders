/**
 * @file screen_object.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __SCREEN_OBJECT_H__
#define __SCREEN_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdlib.h>
#include <stdbool.h>
#include "game_keypresses.h"

//---------------------------------- MACROS -----------------------------------
#define SCREEN_OBJECT_MAX_LENGTH_X (10u)
#define _NEW(class)                ((class *)malloc(sizeof(class)))

//-------------------------------- DATA TYPES ---------------------------------
struct _game_t;
typedef struct _game_t game_t;

typedef struct
{
    void (*task)();
    void (*destroy)();
} screen_object_ops_t;

typedef struct
{
    const screen_object_ops_t *ops;
    bool                       is_alive;
    int                        posX;     // row
    int                        posY;     // collumn
    int                        length_X; // length on screen
    char                       design;   // ASCII design of object
} screen_object_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief Task to be executed each game tick
 *
 * @param key Pressed key
 */
void screen_object_task(screen_object_t *self, game_keypress_t key, game_t *game);

/**
 * @brief Deletes object and frees memory
 */
void screen_object_delete(screen_object_t *self);

#ifdef __cplusplus
}
#endif

#endif // __SCREEN_OBJECT_H__
