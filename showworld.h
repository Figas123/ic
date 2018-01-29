#ifndef SHOWWORLD_H
#define SHOWWORLD_H
/** Enumeracao para defenir o tipo dos agentes para o codigo de visualizacao
    sabes o que imprimir */
typedef enum {
    None    = 0x0, /**< No agent present.     */
    Human   = 0x1, /**< Human agent present.  */
    Zombie  = 0x2, /**< Zombie agent present. */
    Unknown = 0x3  /**< Zombie agent present. */
} AGENT_TYPE;

typedef struct showworld SHOWWORLD;

typedef unsigned int (*get_agent_info_at)(
    void *w,
    unsigned int x,
    unsigned int y);
/** Definir os parametros da funcao que cria um novo showworld */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func);
/** Definir os parametros da funcao que destroi o showworld */
void showworld_destroy(SHOWWORLD *sw);
/** Definir os parametros da funcao que actualiza o showworld */
void showworld_update(SHOWWORLD *sw, void *w);

#endif