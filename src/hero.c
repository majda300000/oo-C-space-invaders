/**
 * @file hero.c
 *
 * @brief Playable character
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "hero.h"
#include "game.h"
#include "game_keypresses.h"
#include <stdlib.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
static void _hero_task(screen_object_t *self, game_keypress_t key);
void        _hero_destroy(screen_object_t *self);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
screen_object_t *hero_new()
{
    hero_t *new_hero = _NEW(hero_t);
    if(new_hero)
    {
        static const screen_object_ops_t hero_ops = {
            .task    = _hero_task,
            .destroy = _hero_destroy,
        };
        new_hero->super.ops      = &hero_ops;
        new_hero->super.posX     = GAME_MAX_X;
        new_hero->super.posY     = GAME_MAX_Y / 2;
        new_hero->super.design   = 'A';
        new_hero->super.length_X = 1;
        new_hero->super.is_alive = true;
    }
    return (screen_object_t *)new_hero;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _hero_task(screen_object_t *self, game_keypress_t key)
{
    if(key == ARROW_RIGHT)
    {
        if(!((self->posY + 1) >= GAME_MAX_Y))
        {
            self->posY++;
        }
    }
    else if(key == ARROW_LEFT)
    {
        if(!((self->posY - 1) < 0))
        {
            self->posY--;
        }
    }
}
void _hero_destroy(screen_object_t *self)
{
    return;
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
