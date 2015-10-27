/*
** pp_die.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Wed Mar  4 09:40:13 2015 Cyril La Valle
** Last update Sun Mar  8 02:23:54 2015 Cyril La Valle
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <execinfo.h>
#include "player.h"

extern int errno;

void	player_die(__attribute__((unused))int sig)
{
  exit(0);
}

void	pp_fatal_die(t_playerinfo *this)
{
  int	nptrs;
  void	*buffer[100];

  fprintf(stderr,
	  "[error] the player at (%hhi, %hhi) dies unexpectedly: %s\n",
	  this->pos.x, this->pos.y, strerror(errno));
  fflush(stderr);
  nptrs = backtrace(buffer, 100);
  backtrace_symbols_fd(buffer, nptrs, 2);
  player_die(0);
}
