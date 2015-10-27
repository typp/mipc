/*
** pp_map_second.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Sat Mar  7 19:22:31 2015 Paul Carensac
** Last update Sun Mar  8 03:10:32 2015 Paul Carensac
*/

#include "player.h"

bool	pp_target_exists(t_playerinfo *pl)
{
  int	idx;
  int	ydx;
  int	map_size;
  int	target_team;

  map_size = g_mem->map_size;
  target_team = MAP[POS(pl->target.x, pl->target.y)];
  if (target_team == pl->id_team)
    return (false);
  if (target_team != 0)
    return (true);
  for (idx = pl->target.x - 1 ; idx < pl->target.x + 2 ; ++idx)
    for (ydx = pl->target.y - 1 ; ydx < pl->target.y + 2 ; ++ydx)
      if (idx >= 0 && idx < map_size && ydx >= 0 && ydx < map_size)
	{
	  target_team = MAP[POS(idx, ydx)];
	  if (target_team != 0 && target_team != pl->id_team)
	    {
	      pl->target.x = idx;
	      pl->target.y = ydx;
	      return (true);
	    }
	}
  return (false);
}

uint8_t		team_living_players(uint8_t id_team, t_player *players)
{
  int		i;
  uint16_t	nb_living;

  i = -1;
  nb_living = 0;
  while (++i <= (g_mem->max_players * g_mem->nb_team) && players[i].team != 0)
    {
      if (players[i].team == id_team)
	++nb_living;
    }
  return (nb_living);
}

bool		pp_team_gathered(t_playerinfo *pl)
{
  int		dist;
  t_player	*players;
  int		i;
  t_xy_list	*list;
  t_xy		center;

  players = PLAYERS;
  list = pp_scan_teammates(pl);
  center.cpt = pp_get_center(list);
  dist = team_living_players(pl->id_team, players) + 2;
  if (dist > 15)
    dist = 15;
  i = -1;
  while (++i <= (g_mem->max_players * g_mem->nb_team) && players[i].team != 0)
    {
      if (players[i].team == pl->id_team)
	{
	  if (MAX(ABS(players[i].posx - center.x),
		  ABS(players[i].posy - center.y)) > dist)
	    return (false);
	}
    }
  return (true);
}
