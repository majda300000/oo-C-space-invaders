/**
 * @file hero.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __HERO_H__
#define __HERO_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
typedef struct
{
    screen_object_t super;
} hero_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief Creates new hero object
 *
 * @return screen_object_t*
 */
screen_object_t *hero_new();

#ifdef __cplusplus
}
#endif

#endif // __HERO_H__
