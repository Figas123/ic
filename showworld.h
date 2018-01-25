#ifndef SHOWWORLD_H
#define SHOWWORLD_H

/**
 * Enumeration which defines a type of agent so that the visualization code
 * knows what to display.
 * */
typedef enum {
    None    = 0x0, /**< No agent present.     */
    Human   = 0x1, /**< Human agent present.  */
    Zombie  = 0x2, /**< Zombie agent present. */
    Unknown = 0x3  /**< Zombie agent present. */
} AGENT_TYPE;

/**
 * The `SHOWWORLD` type is a structure, but the exact fields of that structure
 * are defined in the .c file which implements the interface defined in this
 * .h file. In C this is called a _forward declaration_.
 * */
typedef struct showworld SHOWWORLD;

/**
 * A pointer to a function which returns information about an agent located in
 * the simulation `world` at coordinates (_x_,_y_).
 *
 * @param w Generic pointer to object representing the simulation world. The
 * actual object type should be defined by each project group.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
typedef unsigned int (*get_agent_info_at)(
    void *w,
    unsigned int x,
    unsigned int y);

/**
 * Create a new `SHOWWORLD` object for displaying the game.
 *
 * @param xdim Horizontal dimension of the simulation world (number of columns).
 * @param ydim Vertical dimension of the simulation world (number of rows).
 * @param aginfo_func Pointer to function of type ::get_agent_info_at().
 * @return A new `SHOWWORLD` object for displaying the game.
 * */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func);

/**
 * Destroy a `SHOWWORLD` object.
 *
 * @param sw `SHOWWORLD` object to destroy.
 * */
void showworld_destroy(SHOWWORLD *sw);

/**
 * Updates the display of the simulation world.
 *
 * @param sw Display object.
 * @param w World object (should be defined by each project group).
 * */
void showworld_update(SHOWWORLD *sw, void *w);

#endif
