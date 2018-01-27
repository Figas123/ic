#include "agent.h"
#include "world.h"
#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORLD_X 20
#define WORLD_Y 20
#define MAX_TURNS 1000
#define N_HUMANS 2
#define N_ZOMBIES 1
#define P_HUMANS 1
#define P_ZOMBIES 1

/* This function is an implementation of the definition provided by the
 * ::get_agent_info_at() function pointer. It only works for AGENT and WORLD
 * example structures defined in this file. */
unsigned int example_get_ag_info (void *world, unsigned int x, unsigned int y);

struct agents {
    unsigned int x[100];
    unsigned int y[100];
    unsigned int id[100];
    unsigned int play[100];
    AGENT_TYPE type[100];
};

struct agents ag;

/**
 * This `main` function is only an example of: a) how to use the API defined in
 * the showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided in the
 * showworld_simple.c file).
 *
 * @return Always zero.
 * */
int main() {
	
	int x, y, i, playable;

	/** Inicialicamos o nosso world a null*/
	WORLD *wrld = world_new (WORLD_X, WORLD_Y);

	SHOWWORLD *sw = showworld_new (WORLD_X, WORLD_Y, example_get_ag_info);

	/** Funcao para fazer uma seed de numeros aleatorios */
	srand (time(NULL));

	// Incializar agentes e colocalos aleatoriamente no mundo
	for (i = 0; i < N_HUMANS; i++) {

		x = (rand() % WORLD_X);
		y = (rand() % WORLD_Y);

		if (world_get (wrld, x, y) == NULL) {
			world_put (wrld, x, y, (ITEM *) agent_new (Human, i, i < P_HUMANS));
			ag.id[i] = i;
			ag.type[i] = Human;
			ag.play[i] = playable;
			ag.x[i] = x;
			ag.y[i] = y;
	 	} else {
	 		i--;
	 	}
	}
	for (i = N_HUMANS; i < N_HUMANS + N_ZOMBIES; i++) {

		x = (rand() % WORLD_X);
		y = (rand() % WORLD_Y);

		if (world_get (wrld, x, y) == NULL) {
			world_put (wrld, x, y, (ITEM *) agent_new (Zombie, i, i < N_HUMANS + P_ZOMBIES));
			ag.id[i] = i + N_HUMANS;
			ag.type[i] = Zombie;
			ag.play[i] = playable;
			ag.x[i] = x;
			ag.y[i] = y;
	 	} else {
	 		i--;
	 	}
	}

	for (int turn = 0; turn < MAX_TURNS; turn++) {
		// SCANNER
		for (unsigned int y = 0; y < wrld->ydim; ++y) {

			for (unsigned int x = 0; x < wrld->xdim; ++x) {

				int move = 3;

				for (int na = 0; na < N_HUMANS + N_ZOMBIES; na++) {
					
					int xAnt = ag.x[na];
					int yAnt = ag.y[na];

					for (int i = 1; i <= 3; i++) {

						for (int j = 1; j <= 2; j++) {

							if (move == 4) {
								move = 1;
							} else move += 1;
							for (int block = 1; block <= i; block++) {

								switch (move) {
									case 1:
										// Mexe para a direita i vezes
										ag.x[na] += 1;
										toroidal (&ag.x[na], &ag.y[na]);
										break;
									case 2:
										// Mexe para baixo i vezes
										ag.y[na] += 1;
										toroidal (&ag.x[na], &ag.y[na]);
										break;
									case 3:
										// mexe para esquerda i vezes
										ag.x[na] -= 1;
										toroidal (&ag.x[na], &ag.y[na]);
										break;
									case 4:
										// mexe para cima i vezes
										ag.y[na] -= 1;
										toroidal (&ag.x[na], &ag.y[na]);
										break;
								}
							printf ("Estou no   x:%02d e y:%02d\nComecei no x:%02d e y:%02d\n", ag.x[na], ag.y[na], xAnt, yAnt);
							showworld_update (sw, wrld);
							printf ("Pressione ENTER para o seguinte turno...");
							getchar();
							}
						}
					}
				}	
			}
		}
	}
}

void toroidal (int *x, int *y) {
    int ax = *x;
    int ay = *y;

    if (ax > WORLD_X - 1) {
        ax = 0;
    } else if (ax < 0) {
        ax = WORLD_X - 1;
    }
    if (ay > WORLD_Y - 1) {
        ay = 0;
    } else if (ay < 0) {
        ay = WORLD_Y - 1;
    }

    *x = ax;
    *y = ay;
}

/**
 * This function is an implementation of the ::get_agent_info_at() function
 * definition. It only works for ::AGENT and ::WORLD structures defined in this
 * example.
 *
 * It basically receives a pointer to a ::WORLD structure, obtains the AGENT
 * structure in the given coordinates, and returns the agent information in a
 * bit-packed `unsigned int`.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 *
 * @param w Generic pointer to object representing the simulation world.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
unsigned int example_get_ag_info (void *w, unsigned int x, unsigned int y) {

    /* The agent information to return. */
    unsigned int ag_info = 0;

    /* Convert generic pointer to world to a WORLD object. */
    WORLD *my_world = (WORLD *) w;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
    if ((x >= my_world->xdim) || (y >= my_world->ydim)) {

        /* If we got here, then the coordinates are off bounds. As such we will
           report that the requested agent is of unknown type. No need to
           specify agent ID or playable status, since the agent is unknown. */
        ag_info = Unknown;

    } else {

        /* Given coordinates are within bounds, let's get and pack the request
           agent information. */

        /* Obtain agent at specified coordinates. */
        AGENT *ag = (AGENT *) world_get (my_world, x, y);
		
        /* Is there an agent at (x,y)? */
        if (ag == NULL) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
               None. No need to specify agent ID or playable status, since
               there is no agent here. */
            ag_info = None;

        } else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
               all the agent information as specified by the get_agent_info_at
               function pointer definition. */
            ag_info = (ag->ID << 3) | (ag->playable << 2) | ag->type;

        }

    }

    /* Return the requested agent information. */
    return ag_info;
}
