/**
 * @file block.c
 *
 * @brief Destroyable barrier
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "block.h"
#include "game.h"
#include "game_keypresses.h"
#include <stdlib.h>
#include <time.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
void block_task(screen_object_t *self, game_keypress_t key);
void block_destroy(screen_object_t *self);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
screen_object_t *block_new(int Xrow)
{

    block_t *new_block = _NEW(block_t);
    if(new_block)
    {
        static const screen_object_ops_t block_ops = {
            .task    = block_task,
            .destroy = block_destroy,
        };
        new_block->super.ops      = &block_ops;
        new_block->super.length_X = BLOCK_MIN_LENGTH + rand() % (BLOCK_MAX_LENGTH - BLOCK_MIN_LENGTH + 1);

        new_block->super.posX = Xrow;

        // edge protection
        new_block->super.posY = rand() % (GAME_MAX_Y + 1);
        new_block->super.posY = (new_block->super.posY + new_block->super.length_X) > GAME_MAX_Y ? GAME_MAX_Y - new_block->super.length_X
                                                                                                 : new_block->super.posY;

        new_block->super.is_alive = true;
        new_block->super.design   = '#';

        new_block->health = new_block->super.length_X - 2;
    }
    return (screen_object_t *)new_block;
}

void block_task(screen_object_t *self, game_keypress_t key)
{
    block_t *block_self = (block_t *)self;
    if(block_self->health <= 0)
        block_self->super.is_alive = false;
    return;
}

void block_destroy(screen_object_t *self)
{
    block_t *block_self = (block_t *)self;
    block_self->health  = 0;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
