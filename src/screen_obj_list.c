/**
 * @file screen_obj_list.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <stdlib.h>
#include <string.h>
#include "screen_obj_list.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void screen_obj_list_init(screen_obj_list_t *self)
{
    self->size = 0;
    return;
}

bool screen_obj_list_add(screen_obj_list_t *self, screen_object_t *elem)
{
    if(self->size >= MAX_OBJECTS_ON_SCREEN)
    {
        return false;
    }
    self->elems[self->size] = elem;
    self->size++;
    return true;
}

void screen_obj_list_erase(screen_obj_list_t *self, screen_object_t *elem)
{
    int index;
    for(index = 0; index < self->size; index++)
    {
        if(elem == self->elems[index])
            break;
    }
    // didn't find element
    if(index >= self->size)
        return;

    free(self->elems[index]);
    memmove(&self->elems[index], &self->elems[index + 1], sizeof(screen_object_t *) * (self->size - index - 1));
    self->size--;
    return;
}

size_t screen_obj_list_size(screen_obj_list_t *self)
{
    return self->size;
}

screen_object_t *screen_obj_list_get(screen_obj_list_t *self, size_t index)
{
    if(index >= self->size)
        return NULL;
    return self->elems[index];
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
