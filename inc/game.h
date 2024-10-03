/**
 * @file game.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GAME_H__
#define __GAME_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"
#include "screen_obj_list.h"
#include "game_keypresses.h"

//---------------------------------- MACROS -----------------------------------
/**
 * @brief Game screen dimensions
 *
 */
#define GAME_MAX_Y (32u)
#define GAME_MAX_X (16u)

//-------------------------------- DATA TYPES ---------------------------------
typedef enum
{
    GAME_IN_PROGRESS,
    GAME_HERO_WIN,
    GAME_ALIEN_WIN
} game_state_t;

typedef struct
{
    int num_blocks;
    int alien_rows; // 1 to 3
    int max_bombs;
    int bomb_rate; // in milliseconds
} game_config_t;

typedef struct _game_t
{
    screen_object_t  *hero;
    screen_obj_list_t blocks;
    screen_obj_list_t aliens;
    screen_obj_list_t bombs;

    game_config_t   config;
    game_keypress_t last_pressed; // last pressed key by player
    int             refresh_rate; // in milliseconds
    long            elapsed_time; // in milliseconds
    game_state_t    game_state;
} game_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief Refreshes all screen objects
 *
 * @param self
 */
void game_screen_refresh(game_t *self);

/**
 * @brief Calls all objects tasks
 *
 * @param self
 * @param key Pressed key
 */
void game_mainloop(game_t *self, game_keypress_t key);

/**
 * @brief Initializes all screen objects and game
 *
 * @param config game config
 */
void game_init(game_t *self, game_config_t config);

/**
 * @brief Returns non zero if game over
 *
 * @param self
 * @return int
 */
int game_over(game_t *self);

#ifdef __cplusplus
}
#endif

#endif // __GAME_H__
