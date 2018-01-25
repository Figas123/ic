#include "agent.h"
#include <stdlib.h>

AGENT *agent_new(AGENT_TYPE type, unsigned int ID, char playable) {
    AGENT *agent = NULL;
    agent = malloc(sizeof(AGENT));
    agent->type = type;
    agent->ID = ID;
    agent->playable = playable;
    return agent;
}

void agent_destroy(AGENT *agent) {
    free(agent);
}

