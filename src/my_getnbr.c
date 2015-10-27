/*
** my_getnbr.c for e in /home/carens_p/rendu/PSU_2014_philo/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Thu Feb 26 15:32:44 2015 Paul Carensac
** Last update Sun Mar  8 02:21:48 2015 Cyril La Valle
*/

#include "lemipc.h"

int	my_getnbr(char *str)
{
  int	sign;
  int	nb;
  int	ct;

  sign = 1;
  ct = 0;
  while (str[ct] && ((str[ct] == 45) || (str[ct] == 43)) && ((str[ct] < 48) ||
                                                             (str[ct] > 57)))
    if (str[ct++] == 45)
      sign = -sign;
  nb = 0;
  while (str[ct] && (str[ct] > 47) && (str[ct] < 58))
    nb = nb * 10 + (str[ct++] - 48);
  nb *= sign;
  return (nb);
}
