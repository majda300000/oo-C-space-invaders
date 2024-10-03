# Homework Day 3 - ASCII

## Basic Info

Your task is to implement a console based game like Space Invaders!
Finished gaming screen should look like this:

```
   <___>
        <___>

     o



 [XX]         [XXX]
A
```
Letter `A` represents the **Hero**. Hero is controlled by the player, moves left and right and shoots **bombs** `o` at aliens. **Aliens** are represented with ``<___>`` and are controlled by the game logic, they can also shoot bombs. Blocks `[XX]` in the middle of the screen act as a guard, protecting aliens and the hero from bombs.

The player (Hero) wins if all of the aliens have been destroyed and looses if it gets hit.

## Task Breakdown

### Graphics

For the graphics you should use **ncurses** library. It is used for accessing Linux console in a more user-friendly way. An example application can be found in the initial repository.

### Hero

Hero is controlled by the player. It can move left and right using arrow keys (or any other characters if required for some reason). Space key can be used to shoot bombs towards aliens.

### Aliens

At the top of the screen should be a few rows of alien ships (one ship for each row). They randomly move left and right and they can't go off screen. Aliens must be multiple instances of a same object. Each alien must be its own task, deciding when to switch direction and when to shoot bombs.

### Blocks

Blocks are placed randomly on screen. Size of the block (`[X]` or `[XXX]`) should also be random each game. They don't move and don't shoot bombs, but they can be destroyed if too many bombs hit them.

### Bombs

Bombs can be launched by aliens (going down) and hero (going up). If a bomb hits the Hero, game is over. If it hits one block 4 times, the block is destroyed. If a bomb hits an alien, that alien should disappear.

### Artistic Freedom

Feel free to use different shapes for all on-screen objects. Also you can implement scoring however you wish.

### Game Engine

Cooperative multitasking must be used to implement the game logic. Code must be separated into multiple source files - one per each object.

#### Time Base

Curses is configured to block 1ms for `getch()` function so that the game doesn't consume too much CPU's resources. Because of that, you can only call `getch()` once in each main loop cycle. You can use this limitation to keep track of time by counting ticks (number of `getch()` calls). Keep in mind that `getch()` must be the only function blocking 1ms or more. Measured time can be used to calculate game score.

#### Visible Objects

All visible objects must have the same superclass `screen_obj_t` with the following virtual methods:
- `task` - performs the objects' task. This is an optional method, as some objects may be too dumb to have work to do.
- `delete` - virtual destructor.

Feel free to add additional methods if the implementation could use them commonly for all visible objects.

Virtual destructors enable deleting inherited superclasses. That way a base class (superclass) is requested to be deleted, but a destructor of the inherited subclass is called as it should be. This is how a higher level class can know when its superclass is deleted so it can perform its cleanup. Don't forget to call destructor of the underlying object as well!

All visible objects except Hero must use dynamic allocation. Hero can be a statically allocated object within the games' context.

#### Lists

Aliens, bombs, and blocks are objects that can appear in more than one instance. To simplify handling variable number of such object, a list object can be used.

Implement list object for handling elements of type `screen_obj_t*`. Handling only base class enables using the same list object for all different visible objects.

One list for each object type will be used, i.e. one list for all bombs and one list for all aliens.

The list must use static allocation completely. That will intentionally limit the number of visible objects to some arbitrary number. Let's say 5. So if an object tries to create a 6th bomb it will fail.

The list will fully own its objects! That means it needs to delete them.

The list object will need the following methods:
- `void init(...)` - list initializer
- `void destroy(...)` - list destructor
- `bool add(screen_obj_t*)` - adds a new element, returns false when full
- `void erase(screen_obj_t*)` - finds the element and deletes it
- `size_t size()` - returns number of elements
- `screen_obj_t* get(size_t i)` - returns element on position i or NULL when out of range
- `void clear()` - deletes all elements

Example:

```cpp
alien_t* alien_new(int row);
block_t* block_new();

void game_init(game_t *self)
{
    list_init(&self->aliens);
    for (int i = 0; i < self->config.alien_rows; ++i)
    {
        list_add(&self->aliens, ALIEN_TO_SCROBJ(alien_new(i)));
    }

    list_init(&self->blocks);
    for (int i = 0; i < self->config.num_blocks; ++i)
    {
        list_add(&self->blocks, BLOCK_TO_SCROBJ(block_new()));
    }
}

void game_main_loop(game_t *self)
{
    for (int i = 0; i < list_get_size(&game->aliens); ++i)
    {
        screen_obj_task(list_get(&game->aliens, i));
    }
}

```

#### Game Logic

Every visible object is its own task and acts as an individual. There must not be a global game logic, like a single function handling all objects at once.

Bombs are the only objects that can interact with the other objects. They can be handled in two ways:

- Bombs are dumb and they just fall. Then Blocks, Aliens and Hero need to check for collisions and erase the Bomb.
- Bombs perform collision detection and notify collided objects of the collision, and then delete themselves.
**Hint**: don't forget to call `refresh()` when something on screen is changed. Ideally it should be called only when all changes to screen are done and need to be displayed.

Keys `Q` and `q` can be used to quit the game before the end.
