#include "world_canvas.h"
#include "agent.h"
#include <stdio.h>
#include <stdlib.h>
#include <g2.h>
#include <g2_X11.h>
/** Enumerar as cores */
enum g2_colors {
    GREEN = 7,
    YELLOW = 25
};
/** Funcao para criar um canvas novo */
CANVAS world_canvas_new(WORLD *wrld) {

    int *device;
    device = malloc(sizeof(int));
    /** Abrir janela com g2. Em Windows a funcao chama-se g2_open_win32() */
    *device = g2_open_X11(wrld->xdim * 5, wrld->ydim * 5);
    /** Especificar tamanho e forma dos agentes */
    g2_set_QP(*device, 2, QPcirc);

    return (CANVAS) device;
}
/** Funcao para actualizar o canvas */
void world_canvas_update(CANVAS cnvs, WORLD *wrld) {

    int device = *((int *) cnvs);
    g2_clear(device);

    for (unsigned int y = 0; y < wrld->ydim; ++y) {
        for (unsigned int x = 0; x < wrld->xdim; ++x) {

            AGENT *a = (AGENT *) world_get(wrld, x, y);

            if (a != NULL) {
                switch (a->type) {
                    case Human:
                        g2_pen(device, YELLOW);
                        g2_plot_QP(device, x, y);
                        break;
                    case Zombie:
                        g2_pen(device, GREEN);
                        g2_plot_QP(device, x, y);
                        break;
                    default:
                        /** So vai aqui em caso de erro */
                        fprintf(stderr, "Agente desconhecido!");
                }
            }
        }
    }
}
/** Funcao para destroir a canvas */
void world_canvas_destroy(CANVAS cnvs) {

    g2_close(*((int *) cnvs));
    free(cnvs);
}