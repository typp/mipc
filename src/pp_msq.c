/*
** pp_msq.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Wed Mar  4 08:59:40 2015 Cyril La Valle
** Last update Sun Mar  8 02:07:30 2015 Paul Carensac
*/

#include <string.h>
#include <errno.h>
#include "player.h"

extern int errno;

t_pp_msg	*pp_msq_recv(t_playerinfo *this)
{
  t_pp_msg	*msgbuf;
  ssize_t	msize;

  msgbuf = malloc(sizeof(*msgbuf));
  if (msgbuf == NULL)
    pp_fatal_die(this);
  msize = msgrcv(this->id_msq, msgbuf, PP_MSGSIZ, 0, IPC_NOWAIT);
  if (msize == -1)
    {
      free(msgbuf);
      if (errno == ENOMSG)
	return (NULL);
      else
	pp_fatal_die(this);
    }
  return (msgbuf);
}

void		pp_msq_send(t_playerinfo *this, long type, t_xy_cast pos)
{
  t_pp_msg	msgbuf;

  memset(&msgbuf, 0, sizeof(msgbuf));
  msgbuf.type = type;
  msgbuf.pos.cpt = pos;
  if (msgsnd(this->id_msq, &msgbuf, PP_MSGSIZ, 0) == -1)
    pp_fatal_die(this);
}
