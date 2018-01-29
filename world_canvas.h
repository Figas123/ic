#ifndef WORLD_CANVAS_H
#define WORLD_CANVAS_H

#include "world.h"
#include <stdio.h>

typedef void *CANVAS;
/** Definir os parametros para criar um canvas novo */
CANVAS world_canvas_new(WORLD *wrld);
void world_canvas_update(CANVAS cnvs, WORLD *wrld);
void world_canvas_destroy(CANVAS cnvs);

#endif