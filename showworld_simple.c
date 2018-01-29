#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>

/** Estrutura do showworld */
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};
/** Funcao que cria o showworld */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func) {

    SHOWWORLD *sw = NULL;
    sw = malloc(sizeof(SHOWWORLD));
    sw->xdim = xdim;
    sw->ydim = ydim;
    sw->aginfo_func = aginfo_func;
    return sw;
}
/** Funcao que destroi o showworld */
void showworld_destroy(SHOWWORLD *sw) {
    free(sw);
}
/** Funcao que actualiza o showworld */
void showworld_update(SHOWWORLD *sw, void *w) {

    printf("\n");
    /** Passar por todos os y's */
    for (unsigned int y = 0; y < sw->ydim; ++y) {
        /** Passar por todos os x's */
        for (unsigned int x = 0; x < sw->xdim; ++x) {
            /** Obter o estado do mundo */
            unsigned int item = sw->aginfo_func(w, x, y);
            /** Extrair o tipo do agente (2 bits) */
            AGENT_TYPE ag_type = item & 0x3;
            /** Extrair se o jogador e' jogavel (1 bit) */
            unsigned char playable = (item >> 2) & 0x1;
            /** Extract the agent ID (16 bits). */
            unsigned short ag_id = (item >> 3) & 0xFFFF;
            /** Determinar o tipo do agente */
            switch (ag_type) {
                /** Se nao existir nenhum agente nas coordenadas */
                case None:
                    printf(" .  ");
                    break;
                /** Se existir um humano nas coordenadas */
                case Human:
                    if (playable) {
                        /** Caso o humano for jogavel */
                        printf("H");
                    } else {
                        /** Caso o humano nao seja jogavel */
                        printf("h");
                    }
                    /** Imprimir depois do tipo o id do agente */
                    printf("%02X ", ag_id);
                    break;
                /** If zombie agent present at (x,y) print 'z' or 'Z'. */
                case Zombie:
                    if (playable) {
                        /** Caso o zombie for jogavel */
                        printf("Z");
                    } else {
                        /** Caso o zombie nao seja jogavel */
                        printf("z");
                    }
                    /** Imprimir depois do tipo o id do agente */
                    printf("%02X ", ag_id);
                    break;
                /** Em caso de bug */
                default:
                    printf("?   ");
            }
        }
        /** Imprime 2 paragrafos para no fim da linha */
        printf("\n\n");
    }
    printf("\n");
}
