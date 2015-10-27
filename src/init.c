/*
** init.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 15:33:33 2015 Paul Carensac
** Last update Mon Mar  2 18:43:04 2015 Paul Carensac
*/

#include <string.h>
#include "lemipc.h"

void	init_conf(t_conf *conf)
{
  conf->map_size = MAP_SIZE;
  conf->nb_team = NB_TEAM;
  conf->max_players = MAX_PLAYERS;
}
