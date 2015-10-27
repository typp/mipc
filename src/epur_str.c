/*
** epur_str.c for e in /home/carens_p/rendu/PSU_2014_philo
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Fri Feb 27 15:22:50 2015 Paul Carensac
** Last update Mon Mar  2 18:06:49 2015 Paul Carensac
*/

#include "lemipc.h"

void	overwrite_space(char *buffer, int count)
{
  while (buffer[count])
    {
      buffer[count] = buffer[count + 1];
      count++;
    }
}

void	epur_str(char *buffer)
{
  int	count;
  char	c;

  count = 0;
  while ((c = buffer[count]) != '\0')
    {
      if (SPA(c))
        overwrite_space(buffer, count);
      else
	count++;
    }
}
