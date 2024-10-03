/**
 * @file bomb.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __BOMB_H__
#define __BOMB_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"
#include "game.h"
#include "game_keypresses.h"

//---------------------------------- MACROS -----------------------------------
typedef enum
{
    BOMB_UP,
    BOMB_DOWN
} bomb_direction_t;

typedef struct
{
    screen_object_t  super;
    bomb_direction_t dir; // move direction of bomb
} bomb_t;
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief Creates new Bomb object
 *
 * @param Ycol collumn index
 * @param Xrow row index
 * @param dir bomb direction
 * @return screen_object_t*
 */
screen_object_t *bomb_new(int Ycol, int Xrow, int dir);

#ifdef __cplusplus
}
#endif

#endif // __BOMB_H__
