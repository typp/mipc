/*
** get_next_line.c for e in /home/carens_p/rendu/PSU_2014_philo
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Thu Feb 26 14:36:14 2015 Paul Carensac
** Last update Thu Feb 26 14:53:10 2015 Paul Carensac
*/

#include <unistd.h>
#include <stdlib.h>
#include "gnl.h"

int	is_backslash_n(char *buff, char *keep)
{
  int	count;
  int	count2;

  count = 0;
  count2 = 0;
  while (buff[count] != '\0')
    {
      if (buff[count] == '\n')
	{
	  count = count + 1;
	  while (buff[count] != '\0')
	    {
	      keep[count2++] = buff[count++];
	    }
	  keep[count2] = '\0';
	  return (1);
	}
      count++;
    }
  keep[0] = 0;
  return (0);
}

int	put_in_line(t_strs *strs, char *buff)
{
  int	count;
  int	count2;

  count = 0;
  count2 = 0;
  while (buff[count++] != '\0' && buff[count] != '\n');
  while (strs->line != NULL && (strs->line)[count2++]);
  if ((strs->line_tmp = malloc((count + count2 + 1) * sizeof(char))) == NULL)
    return (1);
  count = 0;
  while (strs->line != NULL && (strs->line)[count])
    {
      (strs->line_tmp)[count] = (strs->line)[count];
      count++;
    }
  count2 = 0;
  while (buff[count2] != '\0' && buff[count2] != '\n')
    (strs->line_tmp)[count++] = buff[count2++];
  (strs->line_tmp)[count] = '\0';
  if (strs->line != NULL)
    free(strs->line);
  strs->line = strs->line_tmp;
  return (0);
}

char		*get_next_line(int fd)
{
  static char	keep[READ_SIZE + 1];
  char		buff[READ_SIZE + 1];
  t_strs	strs;
  int		len;

  strs.line = NULL;
  if (READ_SIZE <= 0)
    return (NULL);
  if (keep[0] != 0)
    {
      if ((put_in_line(&strs, keep)) == 1)
	return (NULL);
      if (is_backslash_n(keep, keep) == 1)
	return (strs.line);
    }
  while ((len = read(fd, buff, READ_SIZE)) > 0)
    {
      buff[len] = '\0';
      if ((put_in_line(&strs, buff)) == 1)
	return (NULL);
      if (is_backslash_n(buff, keep) == 1 || len < READ_SIZE)
	return (strs.line);
    }
  return (strs.line);
}
