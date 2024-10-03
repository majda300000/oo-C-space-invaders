/**
 * @file game_keypresses.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GAME_KEYPRESSES_H__
#define __GAME_KEYPRESSES_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

/**
 * @brief Enum for allowed key controls
 *
 */
typedef enum
{
    ARROW_RIGHT,
    ARROW_LEFT,
    SPACEBAR,
    Q,
    NONE,
} game_keypress_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

#ifdef __cplusplus
}
#endif

#endif // __GAME_KEYPRESSES_H__
