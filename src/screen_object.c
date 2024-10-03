/**
 * @file screen_object.c
 *
 * @brief Superclass for all visible objects
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "screen_object.h"
#include "game.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

void screen_object_task(screen_object_t *self, game_keypress_t key, game_t *game)
{
    self->ops->task(self, key, game);
}

void screen_object_delete(screen_object_t *self)
{
    self->ops->destroy(self);
    self->length_X = 0;
    self->posX     = 0;
    self->posY     = 0;
    // free(self);
    // self->ops      = NULL;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
