#ifndef AGENT_H
#define AGENT_H
#include "showworld.h"
#include "world_canvas.h"
/** Estrutura de AGENT */
typedef struct {
    AGENT_TYPE type;
    unsigned int ID;
    char playable;
} AGENT;
/** Funcao para criar um AGENT */
AGENT *agent_new(AGENT_TYPE type, unsigned int ID, char playable);
void agent_destroy(AGENT *agent);

#endif