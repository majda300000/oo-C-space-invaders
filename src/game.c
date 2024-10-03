/**
 * @file game.c
 *
 * @brief Handles game state
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "game.h"
#include "hero.h"
#include "block.h"
#include "alien.h"
#include "bomb.h"
#include "screen_obj_list.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
static char *_game_build_block(char design, int length, int health);
static char *_game_build_alien(char design, int length);
static void  _game_bomb_generator(game_t *self);
static void  _game_cleanup_objects();
static void  _game_clear_screen();

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void game_screen_refresh(game_t *self)
{
    _game_clear_screen();
    // Hero
    mvprintw(self->hero->posX, 0, "                                ");
    if(self->hero->is_alive)
        mvprintw(self->hero->posX, self->hero->posY, "A");

    // Aliens
    for(int i = 0; i < screen_obj_list_size(&self->aliens); ++i)
    {
        alien_t *alien_i = (alien_t *)screen_obj_list_get(&self->aliens, i);
        mvprintw(alien_i->super.posX, 0, "                                ");
        if(alien_i->super.is_alive)
        {
            char *tmp_alien_string = _game_build_alien(alien_i->super.design, alien_i->super.length_X);
            mvprintw(alien_i->super.posX, alien_i->super.posY, tmp_alien_string);
            free((void *)tmp_alien_string);
        }
    }

    // Blocks
    for(int i = 0; i < screen_obj_list_size(&self->blocks); ++i)
    {
        block_t *block_i = (block_t *)screen_obj_list_get(&self->blocks, i);
        mvprintw(block_i->super.posX, 0, "                                ");
        if(block_i->super.is_alive)
        {
            char *tmp_block_string = _game_build_block(block_i->super.design, block_i->super.length_X, block_i->health);
            mvprintw(block_i->super.posX, block_i->super.posY, tmp_block_string);
            free((void *)tmp_block_string);
        }
    }

    // Bombs
    for(int i = 0; i < screen_obj_list_size(&self->bombs); i++)
    {
        bomb_t *bomb_i = (bomb_t *)screen_obj_list_get(&self->bombs, i);
        if(bomb_i->dir == BOMB_UP)
            mvprintw(bomb_i->super.posX + 1, bomb_i->super.posY, " ");
        else
            mvprintw(bomb_i->super.posX - 1, bomb_i->super.posY, " ");

        if(bomb_i->super.is_alive)
        {
            char bomb_str[2] = "\0";
            bomb_str[0]      = bomb_i->super.design;
            mvprintw(bomb_i->super.posX, bomb_i->super.posY, bomb_str);
        }
    }

    refresh();
}

void game_init(game_t *self, game_config_t config)
{
    self->config = config;

    self->elapsed_time = 0;
    self->refresh_rate = 50;
    self->game_state   = GAME_IN_PROGRESS;

    // init bombs list
    screen_obj_list_init(&self->bombs);

    // init aliens list, add config num of aliens
    screen_obj_list_init(&self->aliens);
    for(int i = 0; i < self->config.alien_rows; ++i)
    {
        screen_obj_list_add(&self->aliens, alien_new(i));
    }

    // init blocks list, add config num of blocks to random unique rows
    screen_obj_list_init(&self->blocks);
    for(int i = 0; i < self->config.num_blocks; ++i)
    {
        int Xrow;

        // check if block already in row
        bool unique_row = false;
        while(!unique_row)
        {
            unique_row = true;
            Xrow       = BLOCK_MIN_X + rand() % (BLOCK_MAX_X - BLOCK_MIN_X);
            for(int j = 0; j < screen_obj_list_size(&self->blocks); j++)
            {
                if(Xrow == screen_obj_list_get(&self->blocks, j)->posX)
                {
                    unique_row = false;
                }
            }
        }

        screen_object_t *block = block_new(Xrow);
        screen_obj_list_add(&self->blocks, block);
    }

    // init hero
    self->hero = hero_new();
}

void game_mainloop(game_t *self, game_keypress_t key)
{
    self->elapsed_time++;

    // add hero bomb if theres space
    if(key == SPACEBAR && (screen_obj_list_size(&self->bombs) < self->config.max_bombs))
    {
        screen_object_t *bomb = bomb_new(self->hero->posY, self->hero->posX - 1, BOMB_UP);
        screen_obj_list_add(&self->bombs, bomb);
    }

    // randomly shoot out alien bombs
    if(self->elapsed_time % self->config.bomb_rate == 0 && (screen_obj_list_size(&self->bombs) < self->config.max_bombs))
    {
        _game_bomb_generator(self);
    }

    // Hero
    screen_object_task(self->hero, key, self);

    // Blocks
    for(int i = 0; i < screen_obj_list_size(&self->blocks); ++i)
    {
        screen_object_t *block = screen_obj_list_get(&self->blocks, i);
        screen_object_task(block, key, self);
    }

    // Aliens & Bombs
    // refresh every .1 seconds
    if(self->elapsed_time % self->refresh_rate == 0)
    {
        // Aliens
        for(int i = 0; i < screen_obj_list_size(&self->aliens); ++i)
        {
            screen_object_task(screen_obj_list_get(&self->aliens, i), key, self);
        }
        // Bombs
        for(int i = 0; i < screen_obj_list_size(&self->bombs); ++i)
        {
            screen_object_task(screen_obj_list_get(&self->bombs, i), key, self);
        }
    }

    _game_cleanup_objects(self);
}

int game_over(game_t *self)
{
    return self->game_state;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

/**
 * @brief Checks if elements still alive after every game tick, removes them if yes
 *
 * @param self
 */
static void _game_cleanup_objects(game_t *self)
{

    // Hero
    if(!self->hero->is_alive)
    {
        self->game_state = GAME_ALIEN_WIN;
        screen_object_delete(self->hero);
    }

    // Blocks
    for(int i = 0; i < screen_obj_list_size(&self->blocks); ++i)
    {
        screen_object_t *block = screen_obj_list_get(&self->blocks, i);
        if(block->is_alive == false)
        {
            screen_obj_list_erase(&self->blocks, block);
        }
    }

    // Aliens
    for(int i = 0; i < screen_obj_list_size(&self->aliens); ++i)
    {
        screen_object_t *alien = screen_obj_list_get(&self->aliens, i);
        if(alien->is_alive == false)
        {
            screen_obj_list_erase(&self->aliens, alien);
        }

        if(screen_obj_list_size(&self->aliens) == 0)
            self->game_state = GAME_HERO_WIN;
    }

    // Bombs
    for(int i = 0; i < screen_obj_list_size(&self->bombs); ++i)
    {
        screen_object_t *bomb = screen_obj_list_get(&self->bombs, i);
        if(bomb->is_alive == false)
        {
            screen_obj_list_erase(&self->bombs, bomb);
        }
    }
}
/**
 * @brief Allocates string for block design
 *
 * @param design character that fills out block
 * @param length length of block
 * @return char* allocate string
 */
static char *_game_build_block(char design, int length, int health)
{
    char *block_string = (char *)malloc((length + 1) * sizeof(char));
    block_string[0]    = '[';
    for(int i = 1; i < length - 1; i++)
    {
        block_string[i] = (i <= health) ? design : ' ';
    }
    block_string[length - 1] = ']';
    block_string[length]     = '\0'; // Null-terminate the string
    return block_string;
}

/**
 * @brief Allocates string for alien design
 *
 * @param design character that fills out alien
 * @param length length of alien
 * @return char*
 *
 * @note ideally should create one function to handle blocks and aliens
 */
static char *_game_build_alien(char design, int length)
{
    char *alien_string = (char *)malloc((length + 1) * sizeof(char));
    alien_string[0]    = '<';
    for(int i = 1; i < length - 1; i++)
    {
        alien_string[i] = design;
    }
    alien_string[length - 1] = '>';
    alien_string[length]     = '\0'; // Null-terminate the string
    return alien_string;
}

/**
 * @brief Randomly generates alien bombs
 *
 */
static void _game_bomb_generator(game_t *self)
{
    int              rand_alien_i = rand() % screen_obj_list_size(&self->aliens);
    screen_object_t *rand_alien   = screen_obj_list_get(&self->aliens, rand_alien_i);
    int              bombX        = rand_alien->posX + 1;
    int              bombY        = rand_alien->posY + rand_alien->length_X / 2 + 1;
    screen_object_t *bomb         = bomb_new(bombY, bombX, BOMB_DOWN);
    screen_obj_list_add(&self->bombs, bomb);
}

/**
 * @brief clear screen after every refresh
 *
 */
static void _game_clear_screen()
{
    for(int i = 0; i < GAME_MAX_X + 1; i++)
    {
        for(int j = 0; j < GAME_MAX_Y; j++)
        {
            mvprintw(i, j, " ");
        }
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
