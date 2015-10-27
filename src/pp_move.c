/*
** pp_move.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Sat Mar  7 23:31:14 2015 Cyril La Valle
** Last update Sat Mar  7 23:31:58 2015 Cyril La Valle
*/

#include "player.h"

int		pp_try_follow_target_x(t_playerinfo *this, uint8_t *map)
{
  int		mov;

  mov = 0;
  if (this->target.x < this->pos.x)
    mov = -1;
  else if (this->target.x > this->pos.x)
    mov = 1;
  if (mov != 0)
    {
      if (map[this->pos.x + mov + this->pos.y * g_mem->map_size] == 0)
	{
	  map[this->pos.x + this->pos.y * g_mem->map_size] = 0;
	  this->pos.x += mov;
	  map[this->pos.x + this->pos.y * g_mem->map_size] = this->id_team;
	}
      else
	mov = 0;
    }
  return (mov != 0);
}

int		pp_try_follow_target_y(t_playerinfo *this, uint8_t *map)
{
  int		mov;

  mov = 0;
  if (this->target.y < this->pos.y)
    mov = -1;
  else if (this->target.y > this->pos.y)
    mov = 1;
  if (mov != 0)
    {
      if (map[this->pos.x + (this->pos.y + mov) * g_mem->map_size] == 0)
	{
	  map[this->pos.x + this->pos.y * g_mem->map_size] = 0;
	  this->pos.y += mov;
	  map[this->pos.x + this->pos.y * g_mem->map_size] = this->id_team;
	}
      else
	mov = 0;
    }
  return (mov != 0);
}

void		pp_try_move(t_playerinfo *this, uint8_t *map)
{
  int		map_size;
  t_xy		pos;

  map = MAP;
  map_size = g_mem->map_size;
  for (pos.x = this->pos.x - 1 ; pos.x <= this->pos.x + 1 ; ++pos.x)
    for (pos.y = this->pos.y - 1 ; pos.y <= this->pos.y + 1 ; ++pos.y)
      if (pos.x >= 0 && pos.x < map_size && pos.y >= 0 && pos.y < map_size &&
	  map[pos.x + pos.y * map_size] == 0)
	{
	  map[this->pos.x + this->pos.y * g_mem->map_size] = 0;
	  this->pos.cpt = pos.cpt;
	  map[this->pos.x + this->pos.y * g_mem->map_size] = this->id_team;
	  return ;
	}
}

void		pp_follow_target(t_playerinfo *this)
{
  uint8_t	*map;
  int		mov;

  mov = 0;
  map = MAP;
  mov = pp_try_follow_target_x(this, map) + pp_try_follow_target_y(this, map);
  if (mov == 0)
    pp_try_move(this, map);
}
