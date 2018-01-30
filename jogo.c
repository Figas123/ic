#include "agent.h"
#include "world.h"
#include "showworld.h"
#include "world_canvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORLD_X 20
#define WORLD_Y 20
#define MAX_TURNS 1000
#define N_HUMANS 2
#define N_ZOMBIES 2
#define P_HUMANS 20
#define P_ZOMBIES 20

/* This function is an implementation of the definition provided by the
 * ::get_agent_info_at() function pointer. It only works for AGENT and WORLD
 * example structures defined in this file. */
unsigned int example_get_ag_info (void *world, unsigned int x, unsigned int y);
/** Estrutura dos agentes */
struct agents {
	unsigned int x[N_HUMANS + N_ZOMBIES];
	unsigned int y[N_HUMANS + N_ZOMBIES];
	unsigned int ID[N_HUMANS + N_ZOMBIES];
	unsigned int play[N_HUMANS + N_ZOMBIES];
	AGENT_TYPE type[N_HUMANS + N_ZOMBIES];
} ag;

int main() {

	unsigned int i;
	/** Inicializamos o mundo a null */
	WORLD *wrld = world_new (WORLD_X, WORLD_Y);
    CANVAS wrld_cnvs = NULL;
    /** Criar canvas onde desenhar o mundo de agentes. */
    wrld_cnvs = world_canvas_new(wrld);
	/** Inicializamos a visualizacao do mundo */
	SHOWWORLD *sw = showworld_new (WORLD_X, WORLD_Y, example_get_ag_info);
	/** Funcao para fazer uma seed de numeros aleatorios */
	srand (time(NULL));
	/** Incializar agentes e colocalos aleatoriamente no mundo */
	/** Criar os Humanos */
	for (i = 0; i < N_HUMANS; ++i) {
		/** Criar variaveis x e y aleatorias */
		unsigned int x = (rand() % WORLD_X);
		unsigned int y = (rand() % WORLD_Y);
		/** Se a coordenada no mundo for null pomo-la um humano */
		if (world_get (wrld, x, y) == NULL) {
			world_put (wrld, x, y, (ITEM *) agent_new (Human, i, i < P_HUMANS));
			ag.ID[i] = i;
			ag.type[i] = Human;
			ag.play[i] = 1;
			ag.x[i] = x;
			ag.y[i] = y;
			printf("Humano %03x   x:%02d y:%02d\n", ag.ID[i], ag.x[i], ag.y[i]);
		}
		/** Se estiver ocupada voltamos o i para tras para não saltar id's */
		else { i--; }
		if (i == N_HUMANS - 1) { printf("\n"); }
	}
	/** Criar os Zombies */
	for (i = N_HUMANS; i < N_HUMANS + N_ZOMBIES; ++i) {
		/** Criar variaveis x e y aleatorias */
		unsigned int x = (rand() % WORLD_X);
		unsigned int y = (rand() % WORLD_Y);
		/** Se a coordenada no mundo for null pomo-la um zombie */
		if (world_get (wrld, x, y) == NULL) {
			world_put (wrld, x, y, (ITEM *) agent_new (Zombie, i, i < N_HUMANS + P_ZOMBIES));
			ag.ID[i] = i;
			ag.type[i] = Zombie;
			ag.play[i] = 1;
			ag.x[i] = x;
			ag.y[i] = y;
			printf("Zombie %03x   x:%02d y:%02d\n", ag.ID[i], ag.x[i], ag.y[i]);
		/** Se estiver ocupada voltamos o i para tras para não saltar id's */
		} else {
			i--;
		}
		if (i == N_HUMANS + N_ZOMBIES - 1) { printf("\n"); }
	}
	/** Inicializar os turnos */
	for (int turn = 0; turn < MAX_TURNS; ++turn) {
		/** Os turnos duram durante a (numero de agentes) */
		for (int a = 0; a < N_HUMANS + N_ZOMBIES; ++a) {
			/** Cria variaveis para memorizar a posicao inicial do agente */
			unsigned int xOLD = ag.x[a];
			unsigned int yOLD = ag.y[a];
			/* Atualizar canvas onde esta' a ser mostrado o mundo de agentes. */
			world_canvas_update(wrld_cnvs, wrld);
			/** Imprime o mundo */
			showworld_update (sw, wrld);
			printf("TURNO  %03d\n\n", turn);
			printf("AGENTE %03d\n\n", ag.ID[a]);
			printf("Estou nas coordenadas x:%02d y:%02d\n\n",ag.x[a], ag.y[a]);
			/** Se o agente for jogavel */
			if (ag.play[a] == 1) {
				/** Cria-se uma variavel para o switch do movimento */
				int move_player = 0;
				/** Cria-se uma variavel para se houver alguma irregularidade
					no movimento se poder voltar um agente atras */
				int error = 0;
				printf("Queres me mover para onde?\n\n");
				/** Recebe o valor digitado e transforma-se na variavel
					move_player */
				scanf("%d", &move_player);
				printf("\n");
				/** Switch para movimentar os agente conforme a variavel move_player */
				switch (move_player) {
					/** Move 1 para a esquerda e 1 para baixo */
					case 1:
						ag.x[a] -= 1;
						ag.y[a] += 1;
						break;
					/** Move 1 para baixo */
					case 2:
						ag.y[a] += 1;
						break;
					/** Move 1 para a direita e 1 para baixo */
					case 3:
						ag.x[a] += 1;
						ag.y[a] += 1;
						break;
					/** Move 1 para a esquerda */
					case 4:
						ag.x[a] -= 1;
						break;
					/** Nao se move */
					case 5:
						break;
					/** Move 1 para a direita */
					case 6:
						ag.x[a] += 1;
						break;
					/** Move 1 para a esquerda e 1 para cima */
					case 7:
						ag.x[a] -= 1;
						ag.y[a] -= 1;
						break;
					/** Move 1 para cima */
					case 8:
						ag.y[a] -= 1;
						break;
					/** Move 1 para a direita e 1 para cima */
					case 9:
						ag.x[a] += 1;
						ag.y[a] -= 1;
						break;
					}
				/** Faz-se duas variaveis com as coordenadas novas */
				unsigned int x = ag.x[a];
				unsigned int y = ag.y[a];
				/** Ajusta as variaveis caso seja necessario */
				toroidal (&ag.x[a], &ag.y[a]);
				toroidal (&x, &y);
				/** Se o jogador escolher o 5 */
				if (move_player == 5) {
					printf("Decidiste nao me mexer...? Interessante.\n");
					printf("Estou nas coordenadas x:%02d y:%02d\n\n",ag.x[a], ag.y[a]);
				}
				/** Se a direcao escolhida for diferente do esperado */
				else if (move_player < 1 || move_player > 9) {
					printf("Digita uma direcao valida por favor.\n");
					printf("Estou nas coordenadas x:%02d y:%02d\n\n",xOLD, yOLD);
					/** Reinicia as variaveis para o agente nao mover */
					ag.x[a] = xOLD;
					ag.y[a] = yOLD;
					/** Como e' um "erro" a variavel error passa a 1 */
					error = 1;
				}
				/** Se a casa escolhida nao estiver ocupada */
				else if (world_get (wrld, x, y) != NULL) {
					printf("Caminho bloqueado, tenta outra direcao.\n");
					printf("Estou nas coordenadas x:%02d y:%02d\n\n",xOLD, yOLD);
					/** Reinicia as variaveis para o agente nao mover */
					ag.x[a] = xOLD;
					ag.y[a] = yOLD;
					/** Como e' um "erro" a variavel error passa a 1 */
					error = 1;
				}
				/** Se a casa escolhida estiver vazia */
				if (world_get (wrld, x, y) == NULL) {
					printf("Estou nas coordenadas x:%02d y:%02d\n\n",ag.x[a], ag.y[a]);
					/** Duplica o agente para o novo id */
					world_put (wrld, x, y, (ITEM *) agent_new (ag.type[a], ag.ID[a], 1));
					/** Apaga o agente no id antigo */
					if (xOLD != ag.x[a] || yOLD != ag.y[a]) {
						world_put (wrld, xOLD, yOLD, NULL);
					}
				}
				/** Se houve algum erro volta um agente para tras */
				if (error == 1) { --a; }
			}
			printf("Pressiona ENTER para passar para o seguinte turno.");
			getchar();

		/** SCANNER (tentativa)

		int move = 3;

		for (int a = 0; a < N_HUMANS + N_ZOMBIES; ++a) {

			int xOLD = ag.x[a];
			int yOLD = ag.y[a];

			int xNEW = ag.x[a];
			int yNEW = ag.y[a];

			for (int l = 1; l <= WORLD_X; ++l) {

				for (int j = 1; j <= 2; ++j) {

					if (move == 4) {
						move = 1;
					} else move += 1;

					for (int scan = 1; scan <= l; ++scan) {

						switch (move) {
							case 1:
							xNEW += 1;
								// Mexe para a direita l vezes
								toroidal (&ag.x[a], &ag.y[a]);
								if (wrld->grid[ag.y[a] * wrld->xdim + ag.x[a]] != NULL) {
									printf("Sou %03d e Encontrei em x:%02d y:%02d	Estou x:%02d y:%02d\n", ag.ID[a], ag.x[a], ag.y[a], xNEW, yNEW);
									move_it (&xNEW, &yNEW, &ag.x[a], &ag.y[a]);
								}
								break;
							case 2:
								yNEW += 1;
								// Mexe para baixo l vezes
								toroidal (&ag.x[a], &ag.y[a]);
								if (wrld->grid[ag.y[a] * wrld->xdim + ag.x[a]] != NULL) {
									printf("Sou %03d e Encontrei em x:%02d y:%02d	Estou x:%02d y:%02d\n", ag.ID[a], ag.x[a], ag.y[a], xNEW, yNEW);
									move_it (&xNEW, &yNEW, &ag.x[a], &ag.y[a]);
								}
								break;
							case 3:
								xNEW -= 1;
								// Mexe para esquerda l vezes
								toroidal (&ag.x[a], &ag.y[a]);
								if (wrld->grid[ag.y[a] * wrld->xdim + ag.x[a]] != NULL) {
									printf("Sou %03d e Encontrei em x:%02d y:%02d	Estou x:%02d y:%02d\n", ag.ID[a], ag.x[a], ag.y[a], xNEW, yNEW);
									move_it (&xNEW, &yNEW, &ag.x[a], &ag.y[a]);
								}
								break;
							case 4:
								yNEW -= 1;
								// Mexe para cima l vezes
								toroidal (&ag.x[a], &ag.y[a]);
								if (wrld->grid[ag.y[a] * wrld->xdim + ag.x[a]] != NULL) {
									printf("Sou %03d e Encontrei em x:%02d y:%02d	Estou x:%02d y:%02d\n", ag.ID[a], ag.x[a], ag.y[a], xNEW, yNEW);
									move_it (&xNEW, &yNEW, &ag.x[a], &ag.y[a]);
								}
								break;
						}
						toroidal (&xNEW, &yNEW);
								toroidal (&ag.x[a], &ag.y[a]);
					}
				}
			}**/
		}
	}
}

void toroidal (int *x, int *y) {
	/** Criam-se variaveis duplicadas dos valores recebidos */
	int ax = *x;
	int ay = *y;
	/** Se o x passar do limite direito o x aparece no limite esquerdo */
	if (ax > WORLD_X - 1) {
		ax = 0;
	}
	/** Se o x passar do limite esquerdo o x aparece no limite direito */
	if (ax < 0) {
		ax = WORLD_X - 1;
	}
	/** Se o y passar do limite inferior o y aparece no limite superior */
	if (ay > WORLD_Y - 1) {
		ay = 0;
	}
	/** Se o y passar do limite superior o y aparece no limite inferior */
	if (ay < 0) {
		ay = WORLD_Y - 1;
	}
	/** Iguala-se o resultado da magia anterior aos apontadores */
	*x = ax;
	*y = ay;
}
/** Movimento (tentativa)
void move_it (int *x, int *y, int *agx, int *agy) {
	int ax = *agx;
	int ay = *agy;
	int bx = *x;
	int by = *y;

	if (ax > bx) {
		if (ay > by) {
			ax += 1;
			ay += 1;
		}
		else if (ay < by) {
			ax += 1;
			ay -= 1;
		}
	}
	else if (ax < bx) {
		if (ay > by) {
			ax -= 1;
			ay += 1;
		}
		else if (ay < by) {
			ax -= 1;
			ay -= 1;
		}
	}
	if (ax == bx) {
		if (ay > bx) {
			ay -= 1;
		}
		else if (ay < bx) {
			ay += 1;
		}
	}
	else if (ay == by) {
		if (ax > by) {
			ax -= 1;
		}
		else if (ax < by) {
			ax += 1;
		}
	}
	
	*agx = ax;
	*agy = ay;
	*x = bx;
	*y = by;
} */
unsigned int example_get_ag_info (void *w, unsigned int x, unsigned int y) {

	unsigned int ag_info = 0;
	/** Converte um apontador generico para o mundo num objeto WORLD */
	WORLD *my_world = (WORLD *) w;
	/** Verificar se as coordenadas estao dentro dos limites do mundo */
	/** Se o agente estiver fora dos limtes este fica como "Unknow" */
	if ((x >= my_world->xdim) || (y >= my_world->ydim)) {
		ag_info = Unknown;
	}
	/** Se o agente estiver dentro */
	else {
		/** Obtem coordenadas */
		AGENT *ag = (AGENT *) world_get (my_world, x, y);
		/** Se nao houver agentes nas coordenadas as coordenadas ficam como "None" */
		if (ag == NULL) {
			ag_info = None;
		}
		/** Se houver agente nas coordenadas extrai-se as informacoes do agente */
		else {
			ag_info = (ag->ID << 3) | (ag->playable << 2) | ag->type;
		}
	}
	/** Devolver a informacao do agente */
	return ag_info;
}