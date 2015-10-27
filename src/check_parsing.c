/*
** check_parsing.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 18:03:10 2015 Paul Carensac
** Last update Sun Mar  8 03:11:18 2015 Paul Carensac
*/

#include "lemipc.h"

int	check_config(t_conf *conf)
{
  if (conf->map_size < 10 || conf->map_size > 100)
    {
      fprintf(stderr, "map size must be betwenn 10 and 100\n");
      return (1);
    }
  if (conf->nb_team < 2 || conf->nb_team > 4)
    {
      fprintf(stderr, "team number must be betwenn 2 and 4\n");
      return (1);
    }
  if (conf->max_players < 2 || conf->max_players > (conf->map_size - 1))
    {
      fprintf(stderr, "max team players must be between 2 and \
(map_size - 1)\n");
      return (1);
    }
  return (0);
}

void	print_warning(char *text, int line_nb)
{
  fprintf(stderr, "Warning: %s line %d.\n", text, line_nb);
}
