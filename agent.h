#ifndef AGENT_H
#define AGENT_H
#include "showworld.h"

typedef struct {
    AGENT_TYPE type;
    unsigned int ID;
    char playable;
} AGENT;

AGENT *agent_new(AGENT_TYPE type, unsigned int ID, char playable);
void agent_destroy(AGENT *agent);

#endif
