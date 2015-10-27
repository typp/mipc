/*
** pp_map.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Wed Mar  4 10:48:04 2015 Cyril La Valle
** Last update Sun Mar  8 03:01:20 2015 Paul Carensac
*/

#include "player.h"

t_xy_list	*pp_scan_teammates(t_playerinfo *this)
{
  t_player	*parray;
  t_xy_list	*list;
  unsigned	idx;
  t_xy		pos;

  parray = PLAYERS;
  list = NULL;
  for (idx = 0 ; parray[idx].team != 0 ; ++idx)
    {
      if (parray[idx].team == this->id_team)
	{
	  pos.x = parray[idx].posx;
	  pos.y = parray[idx].posy;
	  if (xy_list_append(&list, pos.cpt) == -1)
	    pp_fatal_die(this);
	}
    }
  return (list);
}

t_xy_cast	pp_get_center(t_xy_list *list)
{
  t_xy_list	*nptr;
  t_xy		center;
  int32_t	x;
  int32_t	y;
  int32_t	nbp;

  center.cpt = 0;
  x = 0;
  y = 0;
  nbp = 0;
  for (nptr = list ; nptr != NULL ; nptr = nptr->next)
    {
      x += nptr->data.x;
      y += nptr->data.y;
      nbp++;
    }
  if (nbp)
    {
      center.x = x / nbp;
      center.y = y / nbp;
    }
  return (center.cpt);
}

bool		pp_player_exists(t_player *players, t_xy *pos, uint8_t *map)
{
  int		i;

  i = -1;
  while (++i <= (g_mem->max_players * g_mem->nb_team) && players[i].team != 0)
    {
      if (players[i].alive && players[i].posx == pos->x &&
	  players[i].posy == pos->y)
	return (true);
    }
  map[POS(pos->x, pos->y)] = 0;
  return (false);
}

t_xy_cast	pp_target_enemy(t_playerinfo const *this)
{
  uint8_t	*map;
  int		map_size;
  int		radius;
  t_xy		pos;

  map = MAP;
  map_size = g_mem->map_size;
  for (radius = 1 ;
       radius < map_size ;
       ++radius)
    for (pos.x = this->pos.x - radius ;
	 pos.x <= this->pos.x + radius ;
	 ++pos.x)
      for (pos.y = this->pos.y - radius ;
	   pos.y <= this->pos.y + radius ;
	   ++pos.y)
	if (pos.x >= 0 && pos.x < map_size && pos.y >= 0 && pos.y < map_size &&
	    map[pos.x + pos.y * map_size] != 0 &&
	    map[pos.x + pos.y * map_size] != this->id_team &&
	    pp_player_exists(PLAYERS, &pos, map))
	  return (pos.cpt);
  return (-1);
}
