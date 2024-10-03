/**
 * @file block.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __BLOCK_H__
#define __BLOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"
//---------------------------------- MACROS -----------------------------------
#define BLOCK_MIN_X (3)
#define BLOCK_MAX_X (15)

#define BLOCK_MIN_LENGTH (4)
#define BLOCK_MAX_LENGTH (7)

//-------------------------------- DATA TYPES ---------------------------------
typedef struct
{
    screen_object_t super;
    int             health;
} block_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief Creates new block object
 *
 * @return screen_object_t*
 */
screen_object_t *block_new();

#ifdef __cplusplus
}
#endif

#endif // __BLOCK_H__
