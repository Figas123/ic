#include "agent.h"
#include <stdlib.h>
/** Funcao para criar um agente novo */
AGENT *agent_new(AGENT_TYPE type, unsigned int ID, char playable) {
	AGENT *agent = NULL;
	agent = malloc(sizeof(AGENT));
	agent->type = type;
	agent->ID = ID;
	agent->playable = playable;
	return agent;
}
/** Funcao para destroir um agente */
void agent_destroy(AGENT *agent) {
	free(agent);
}

