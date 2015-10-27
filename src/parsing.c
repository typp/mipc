/*
** parsing.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 15:47:46 2015 Paul Carensac
** Last update Wed Mar  4 10:05:39 2015 Paul Carensac
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "lemipc.h"

void	replace_comm(char *line)
{
  int	i;

  i = 0;
  while (line[i])
    {
      if (line[i] == '#')
	line[i] = '\0';
      i++;
    }
}

void	get_conf_number(char *src, uint8_t *dest, int line_nb)
{
  if (src[0] == '\0' || strspn(src, "0123456789") != strlen(src))
    {
      print_warning("An argument must be a positive number", line_nb);
      return ;
    }
  *dest = (uint8_t)my_getnbr(src);
}

void	parse_line(char *line, t_conf *conf, int line_nb)
{
  int	i;

  i = 0;
  while (line[i] && line[i] != '=')
    ++i;
  if (!line[i])
    {
      print_warning("Syntax error (missing '=')", line_nb);
      return ;
    }
  line[i] = '\0';
  if (!strcmp(line, "map_size"))
    get_conf_number(&(line[i + 1]), &(conf->map_size), line_nb);
  else if (!strcmp(line, "nb_team"))
    get_conf_number(&(line[i + 1]), &(conf->nb_team), line_nb);
  else if (!strcmp(line, "max_team_players"))
    get_conf_number(&(line[i + 1]), &(conf->max_players), line_nb);
  else
    print_warning("Unknown instruction", line_nb);
}

void	parse_config(char *file, t_conf *conf)
{
  int	fd;
  char	*line;
  int	line_nb;

  if ((fd = open(file, O_RDONLY)) < 0)
    {
      fprintf(stderr, "Open failed\n");
      return ;
    }
  line_nb = 1;
  while ((line = get_next_line(fd)) != NULL)
    {
      replace_comm(line);
      epur_str(line);
      if (strlen(line))
	{
	  parse_line(line, conf, line_nb);
	}
      free(line);
      ++line_nb;
    }
  close(fd);
}
