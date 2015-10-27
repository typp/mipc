/*
** lemipc.h for e7 in /home/carens_p/rendu/PSU_2014_lemipc
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 11:02:31 2015 Paul Carensac
** Last update Sun Mar  8 02:25:24 2015 Cyril La Valle
*/

#ifndef LEMIPC_H_
#define LEMIPC_H_

#include "gnl.h"
#include "mem.h"

#define MAP_SIZE 50
#define NB_TEAM 2
#define MAX_PLAYERS 10

#define ABS(x) (((x) < 0) ? -(x) : (x))
#define SPA(c) (((c) == ' ' || (c) == '\t') ? (1) : (0))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct	s_conf
{
  size_t	total_size;
  uint8_t	map_size;
  uint8_t	nb_team;
  uint8_t	max_players;
}		t_conf;

typedef struct	s_keys
{
  key_t		global_key;
  int		shm_id;
  int		sem_id;
  int		msg_id[4];
}		t_keys;

/*
** main.c
*/
void	player_die(int sig);
void	change_shm_state(bool);
void	delete_ipcs();

/*
** init.c
*/
void	init_conf(t_conf *conf);

/*
** parsing.c
*/
void	parse_config(char *file, t_conf *conf);

/*
** check_parsing.c
*/
int	check_config(t_conf *conf);
void	print_warning(char *text, int line_nb);

/*
** create_ipcs.c
*/
int	create_keys(char *path, t_conf *conf, t_keys *, t_player **);

/*
** init_player.c
*/
int	set_player(t_keys *, t_player **);

/*
** other
*/
int	my_getnbr(char *str);
void	epur_str(char *str);

/*
** player_play.c
*/
void	player_play(t_keys *keys, t_player *player);

#endif
