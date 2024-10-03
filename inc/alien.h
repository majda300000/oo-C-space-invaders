/**
 * @file alien.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __ALIEN_H__
#define __ALIEN_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"
//---------------------------------- MACROS -----------------------------------
#define ALIEN_LENGTH_X (5)
//-------------------------------- DATA TYPES ---------------------------------
typedef enum
{
    ALIEN_RIGHT,
    ALIEN_LEFT
} alien_direction_t;

typedef struct
{
    screen_object_t   super;
    alien_direction_t dir; // move direction of alien
} alien_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief Creates new alien object
 *
 * @param row X coordinate the alien will be placed to
 */
screen_object_t *alien_new(int row);

#ifdef __cplusplus
}
#endif

#endif // __ALIEN_H__
