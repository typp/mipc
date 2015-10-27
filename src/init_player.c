/*
** init_player.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Tue Mar  3 10:32:54 2015 Paul Carensac
** Last update Sat Mar  7 11:28:13 2015 Paul Carensac
*/

#include <time.h>
#include "lemipc.h"

int	find_player_team(t_player **player)
{
  int	i;
  int	nb_players;

  i = -1;
  nb_players = g_mem->nb_team * g_mem->max_players;
  while (++i < nb_players)
    {
      if (PLAYERS[i].team == 0)
	{
	  *player = &(PLAYERS[i]);
	  (*player)->team = (i % g_mem->nb_team) + 1;
	  return (0);
	}
    }
  return (-1);
}

void	set_player_pos(t_player *player)
{
  int	pos;
  int	mi_map;

  mi_map = g_mem->map_size / 2;
  while (1)
    {
      player->posx = random() % (mi_map);
      player->posy = random() % (mi_map);
      if (player->team % 2 == 0)
	player->posx += mi_map;
      if (player->team / 3 == 1)
	player->posy += mi_map;
      pos = g_mem->map_size * player->posy + player->posx;
      if (MAP[pos] == 0)
	{
	  MAP[pos] = player->team;
	  return ;
	}
    }
}

int		set_player(t_keys *keys, t_player **player)
{
  void		*addr;

  if (g_mem == NULL)
    {
      if ((addr = shmat(keys->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
	return (fprintf(stderr, "Failed to retrieve shared memory adress\n"));
      g_mem = addr;
    }
  if (find_player_team(player) < 0)
    return (fprintf(stderr, "All player slots are full. Sorry.\n"));
  (*player)->round = 0;
  (*player)->alive = true;
  (*player)->attacking = false;
  srandom(time(0) * getpid());
  set_player_pos(*player);
  g_mem->living_players += 1;
  return (0);
}
