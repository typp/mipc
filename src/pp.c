/*
** pp.c for LemIPC in /home/la-val_c/rendu/PSU_2014_lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Tue Mar  3 19:44:43 2015 Cyril La Valle
** Last update Sun Mar  8 03:19:02 2015 Paul Carensac
*/

#include "player.h"

int		pp_enter(t_playerinfo *this)
{
  t_pp_msg	*msg;

  msg = pp_msq_recv(this);
  if (msg == NULL)
    pp_without_message(this);
  else
    {
      pp_with_message(this, msg);
      free(msg);
    }
  pp_follow_target(this);
  return (0);
}

void	pp_without_message(t_playerinfo *this)
{
  if (pp_team_gathered(this))
    {
      pp_attack(this);
    }
  else
    {
      pp_gather(this);
    }
}

void	pp_with_message(t_playerinfo *this, t_pp_msg *msg)
{
  this->target.cpt = msg->pos.cpt;
  if (msg->type == PP_MSG_GATHER)
    {
      if (pp_team_gathered(this))
	pp_attack(this);
    }
  else if (msg->type == PP_MSG_ATTACK)
    {
      if (!pp_target_exists(this))
	pp_attack(this);
    }
  pp_msq_send(this, msg->type, msg->pos.cpt);
}

void	pp_attack(t_playerinfo *this)
{
  this->target.cpt = pp_target_enemy(this);
  if (this->target.cpt != -1)
    pp_msq_send(this, PP_MSG_ATTACK, this->pos.cpt);
  else
    pp_gather(this);
}

void		pp_gather(t_playerinfo *this)
{
  t_xy_list	*list;

  list = pp_scan_teammates(this);
  if (list == NULL)
    pp_fatal_die(this);
  this->target.cpt = pp_get_center(list);
  pp_msq_send(this, PP_MSG_GATHER, this->pos.cpt);
}
