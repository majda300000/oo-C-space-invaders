/**
 * @file bomb.c
 *
 * @brief Moving missile
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "bomb.h"
#include "block.h"
#include "alien.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
void        _bomb_task(screen_object_t *self, game_keypress_t key, game_t *game);
void        _bomb_destroy(screen_object_t *self);
static void _bomb_check_collisions(screen_object_t *self, game_t *game);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
screen_object_t *bomb_new(int Ycol, int Xrow, int dir)
{

    bomb_t *new_bomb = _NEW(bomb_t);
    if(new_bomb)
    {
        static const screen_object_ops_t bomb_ops = {
            .task    = _bomb_task,
            .destroy = _bomb_destroy,
        };
        new_bomb->super.ops      = &bomb_ops;
        new_bomb->super.length_X = 1;

        new_bomb->super.posX = Xrow;
        new_bomb->super.posY = Ycol;

        new_bomb->super.is_alive = true;
        new_bomb->dir            = dir;

        new_bomb->super.design = dir ? 'v' : '^';
    }
    return (screen_object_t *)new_bomb;
}

void _bomb_task(screen_object_t *self, game_keypress_t key, game_t *game)
{
    bomb_t *bomb_self = (bomb_t *)self;
    if(bomb_self->dir == BOMB_UP)
    {
        bomb_self->super.posX--;
        if(bomb_self->super.posX < 0)
            bomb_self->super.is_alive = false;
    }
    else if(bomb_self->dir == BOMB_DOWN)
    {
        bomb_self->super.posX++;
        if(bomb_self->super.posX > GAME_MAX_X)
            bomb_self->super.is_alive = false;
    }

    // TODO: check collisions
    _bomb_check_collisions(self, game);

    return;
}

void _bomb_destroy(screen_object_t *self)
{
    bomb_t *bomb_self = (bomb_t *)self;
    bomb_self->dir    = 0;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static void _bomb_check_collisions(screen_object_t *self, game_t *game)
{
    int bombX    = self->posX;
    int bombY    = self->posY;
    int bomb_dir = ((bomb_t *)self)->dir;

    // Aliens
    for(int i = 0; i < screen_obj_list_size(&game->aliens); ++i)
    {
        screen_object_t *alien = screen_obj_list_get(&game->aliens, i);
        if((bombX == alien->posX) && (bombY >= alien->posY) && (bombY <= (alien->posY + alien->length_X)) && (bomb_dir == BOMB_UP))
        {
            alien->is_alive = false;
            self->is_alive  = false;
        }
    }

    // Blocks
    for(int i = 0; i < screen_obj_list_size(&game->blocks); ++i)
    {
        screen_object_t *block = screen_obj_list_get(&game->blocks, i);
        if((bombX == block->posX) && (bombY >= block->posY) && (bombY <= (block->posY + block->length_X)))
        {
            ((block_t *)block)->health--;
            if(((block_t *)block)->health == 0)
                block->is_alive = false;
            self->is_alive = false;
        }
    }

    // Hit Hero
    if((game->hero->posX == bombX) && (game->hero->posY == bombY) && (bomb_dir == BOMB_DOWN))
    {
        game->hero->is_alive = false;
        self->is_alive       = false;
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
