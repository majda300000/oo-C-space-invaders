/**
* @file main.c

* @brief Application code.

* @par Application code.
*
* COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

//--------------------------------- INCLUDES ----------------------------------
#include <ncurses.h>
#include <stdbool.h>
#include "screen_object.h"
#include "hero.h"
#include "screen_obj_list.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

// global game control variable
game_t game;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
int main(void)
{
    srand(time(NULL));

    initscr();
    raw();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, TRUE);
    timeout(1);

    mvprintw(GAME_MAX_X + 2, 0, "press q to exit");

    game_config_t conf = {
        .alien_rows = 3,
        .bomb_rate  = 500,
        .max_bombs  = 10,
        .num_blocks = 5,
    };
    game_init(&game, conf);

    int is_game_over = 0;

    // game loop
    while(!is_game_over)
    {
        // check if game is over every game tick
        is_game_over = game_over(&game);

        // check if player pressed any key
        game_keypress_t key = NONE;
        switch(getch())
        {
            case KEY_LEFT:
                key = ARROW_LEFT;
                break;
            case KEY_RIGHT:
                key = ARROW_RIGHT;
                break;
            case ' ':
                key = SPACEBAR;
                break;
            case 'q':
            case 'Q':
                is_game_over = true;
                break;
            default:
                key = NONE;
                break;
        }
        game_mainloop(&game, key);
        game_screen_refresh(&game);
    }

    // game over
    switch(is_game_over)
    {
        case GAME_ALIEN_WIN:
            mvprintw(GAME_MAX_X / 2, GAME_MAX_Y / 3, "ALIENS WIN !");
            break;
        case GAME_HERO_WIN:
            mvprintw(GAME_MAX_X / 2, GAME_MAX_Y / 3, "HERO WINS !");
            break;
        default:
            break;
    }

    while(1)
    {
        if(getch() == 'q')
            break;
    }

    endwin();
    return 0;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
