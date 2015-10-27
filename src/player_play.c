/*
** player_s.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Wed Mar  4 18:48:33 2015 Cyril La Valle
** Last update Sun Mar  8 03:02:01 2015 Paul Carensac
*/

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include "lemipc.h"
#include "player.h"

extern int errno;

void		pp_round_enter(t_keys *keys, t_playerinfo *pinfo)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  if (semop(keys->sem_id, &sops, 1) == -1)
    pp_fatal_die(pinfo);
}

void		pp_round_leave(t_keys *keys, t_player *player,
			       t_playerinfo *pinfo)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  if (semop(keys->sem_id, &sops, 1) == -1)
    pp_fatal_die(pinfo);
  ++player->round;
  player->posx = pinfo->pos.x;
  player->posy = pinfo->pos.y;
  usleep(200000);
}

int		pp_can_run(t_playerinfo *pinfo)
{
  uint8_t	*map;
  uint8_t	map_size;
  uint8_t	team;
  int32_t	idx;
  int32_t	ydx;
  unsigned	enemies;

  enemies = 0;
  map = MAP;
  map_size = g_mem->map_size;
  for (team = 1 ; team < g_mem->nb_team ; ++team)
    {
      enemies = 0;
      if (team != pinfo->id_team)
	for (idx = pinfo->pos.x - 1 ; idx < pinfo->pos.x + 2 ; ++idx)
	  for (ydx = pinfo->pos.y - 1 ; ydx < pinfo->pos.y + 2 ; ++ydx)
	    if (idx >= 0 && idx < map_size && ydx >= 0 && ydx < map_size &&
		map[idx + ydx * map_size] == team)
	      if (++enemies > 1)
		return (-1);
    }
  return (0);
}

int		pp_killed(t_player *player)
{
  player->alive = false;
  return (0);
}

void		player_play(t_keys *keys, t_player *player)
{
  t_playerinfo	pinfo;

  pinfo.pos.x = player->posx;
  pinfo.pos.y = player->posy;
  pinfo.target.cpt = 0;
  pinfo.id_team = player->team;
  pinfo.id_msq = keys->msg_id[player->team - 1];
  while (player->alive && pp_target_enemy(&pinfo) != -1)
    {
      pp_round_enter(keys, &pinfo);
      if (pp_can_run(&pinfo) == -1)
	pp_killed(player);
      else
	pp_enter(&pinfo);
      pp_round_leave(keys, player, &pinfo);
    }
  if (player->alive)
    {
      sleep(2);
      g_mem->winning_team = player->team;
    }
}
