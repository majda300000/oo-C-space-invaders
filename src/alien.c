/**
 * @file alien.c
 *
 * @brief RNG enemy
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "alien.h"
#include "game.h"
#include "game_keypresses.h"
#include <stdlib.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
void alien_task(screen_object_t *self, game_keypress_t key);
void alien_destroy(screen_obj_list_t *self);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
screen_object_t *alien_new(int Xrow)
{
    alien_t *new_alien = _NEW(alien_t);
    if(new_alien)
    {
        static const screen_object_ops_t alien_ops = {
            .task    = alien_task,
            .destroy = alien_destroy,
        };
        new_alien->super.ops      = &alien_ops;
        new_alien->super.length_X = ALIEN_LENGTH_X;

        new_alien->super.posX = Xrow;

        // edge protection
        new_alien->super.posY = rand() % (GAME_MAX_Y + 1);
        new_alien->super.posY = GAME_MAX_Y / 2 - new_alien->super.length_X / 2;

        new_alien->super.is_alive = true;
        new_alien->super.design   = '_';
    }
    return (screen_object_t *)new_alien;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
void alien_task(screen_object_t *self, game_keypress_t key)
{
    alien_t *a = (alien_t *)self;

    // reached and of screen
    if(((a->super.posY + a->super.length_X >= GAME_MAX_Y) && (a->dir == ALIEN_RIGHT)) || (a->super.posY <= 0) && (a->dir == ALIEN_LEFT))
    {
        a->dir = !a->dir; // switch direction
    }
    // randomly change dir
    else
    {
        float keep_dir_probability = 0.9; // 90% chance to stay the same
        float random_value         = (float)rand() / RAND_MAX;

        // decide whether to toggle or not
        if(random_value > keep_dir_probability)
        {
            // toggle direction
            a->dir = !a->dir;
        }
    }

    // move alien
    if(a->dir == ALIEN_LEFT)
    {
        a->super.posY--;
    }
    else if(a->dir == ALIEN_RIGHT)
    {
        a->super.posY++;
    }
}

void alien_destroy(screen_obj_list_t *self)
{
    alien_t *alien_self = (alien_t *)self;
    alien_self->dir     = 0;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
